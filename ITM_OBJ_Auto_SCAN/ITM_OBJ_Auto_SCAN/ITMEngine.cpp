#include "UI/ITMEngine.h"

ITMEngine::ITMEngine(char* calibFile, char* filename1, char* filename2 , char* imuFile)
	: _calibFile(calibFile), _filename1(filename1), _filename2(filename2), _imuFile(imuFile)
{
}

void ITMEngine::SetGrabberSubject(ISubject* subject)
{
	_subject = subject;
}

void ITMEngine::StartProcessing()
{
	CreateImageSource();

	ITMLibSettings *internalSettings = new ITMLibSettings();
	switch (internalSettings->libMode)
	{
	case ITMLibSettings::LIBMODE_BASIC:
		_mainEngine = new ITMBasicEngine<ITMVoxel, ITMVoxelIndex>(internalSettings, _imageSource->getCalib(), _imageSource->getRGBImageSize(), _imageSource->getDepthImageSize());
		break;
	case ITMLibSettings::LIBMODE_BASIC_SURFELS:
		_mainEngine = new ITMBasicSurfelEngine<ITMSurfelT>(internalSettings, _imageSource->getCalib(), _imageSource->getRGBImageSize(), _imageSource->getDepthImageSize());
		break;
	case ITMLibSettings::LIBMODE_LOOPCLOSURE:
		_mainEngine = new ITMMultiEngine<ITMVoxel, ITMVoxelIndex>(internalSettings, _imageSource->getCalib(), _imageSource->getRGBImageSize(), _imageSource->getDepthImageSize());
		break;
	default:
		throw std::runtime_error("Unsupported library mode!");
		break;
	}

	int textHeight = 30; // Height of text area
						 //winSize.x = (int)(1.5f * (float)MAX(imageSource->getImageSize().x, imageSource->getDepthImageSize().x));
						 //winSize.y = MAX(imageSource->getRGBImageSize().y, imageSource->getDepthImageSize().y) + textHeight;
	_winSize.x = (int)(1.5f * (float)(_imageSource->getDepthImageSize().x));
	_winSize.y = _imageSource->getDepthImageSize().y + textHeight;
	float h1 = textHeight / (float)_winSize.y, h2 = (1.f + h1) / 2;
	_winReg[0] = Vector4f(0.0f, h1, 0.665f, 1.0f);   // Main render
	_winReg[1] = Vector4f(0.665f, h2, 1.0f, 1.0f);   // Side sub window 0
	_winReg[2] = Vector4f(0.665f, h1, 1.0f, h2);     // Side sub window 2

	bool allocateGPU = false;
	if (internalSettings->deviceType == ITMLibSettings::DEVICE_CUDA) allocateGPU = true;

	for (int w = 0; w < NUM_WIN; w++)
		_outImage[w] = new ITMUChar4Image(_imageSource->getDepthImageSize(), true, allocateGPU);

	_inputRGBImage = new ITMUChar4Image(_imageSource->getRGBImageSize(), true, allocateGPU);
	_inputRawDepthImage = new ITMShortImage(_imageSource->getDepthImageSize(), true, allocateGPU);
	_inputIMUMeasurement = new ITMIMUMeasurement();

	//_saveImage = new ITMUChar4Image(_imageSource->getDepthImageSize(), true, false);

	_outImageType[0] = ITMMainEngine::InfiniTAM_IMAGE_ORIGINAL_DEPTH;
	//_outImageType[1] = ITMMainEngine::InfiniTAM_IMAGE_ORIGINAL_DEPTH;
	//_outImageType[2] = ITMMainEngine::InfiniTAM_IMAGE_ORIGINAL_RGB;
	//if (_inputRGBImage->noDims == Vector2i(0, 0)) _outImageType[2] = ITMMainEngine::InfiniTAM_IMAGE_UNKNOWN;

	sdkCreateTimer(&_timer_instant);
	sdkCreateTimer(&_timer_average);

	sdkResetTimer(&_timer_average);
}

void ITMEngine::ProcessFrame()
{
	if (!_imageSource->hasMoreImages()) return;
	_imageSource->getImages(_inputRGBImage, _inputRawDepthImage);

	if (_imuSource != NULL) {
		if (!_imuSource->hasMoreMeasurements()) return;
		else _imuSource->getMeasurement(_inputIMUMeasurement);
	}

	sdkResetTimer(&_timer_instant);
	sdkStartTimer(&_timer_instant); sdkStartTimer(&_timer_average);

	ITMTrackingState::TrackingResult trackerResult;
	//actual processing on the mailEngine
	if (_imuSource != NULL) trackerResult = _mainEngine->ProcessFrame(_inputRGBImage, _inputRawDepthImage, _inputIMUMeasurement);
	else trackerResult = _mainEngine->ProcessFrame(_inputRGBImage, _inputRawDepthImage);

	_trackingResult = (int)trackerResult;

#ifndef COMPILE_WITHOUT_CUDA
	ORcudaSafeCall(cudaThreadSynchronize());
#endif
	sdkStopTimer(&_timer_instant); sdkStopTimer(&_timer_average);

	//processedTime = sdkGetTimerValue(&timer_instant);
	_processedTime = sdkGetAverageTimerValue(&_timer_average);

	DisplayImage();
}

void ITMEngine::DisplayImage()
{
	_mainEngine->GetImage(_outImage[0], _outImageType[0]);
	ITMUChar4Image** showImgs = _outImage;
	Vector4f* winReg = _winReg;
	Vector4u* cpuData = showImgs[0]->GetData(MEMORYDEVICE_CPU);
	size_t size = showImgs[0]->dataSize;
}

void ITMEngine::CreateImageSource()
{
	if (_subject == NULL)
	{
		return;
	}
	if (strcmp(_calibFile, "viewer") == 0)
	{
		_imageSource = new BlankImageGenerator("", Vector2i(640, 480));
		printf("starting in viewer mode: make sure to press n first to initiliase the views ... \n");
		return;
	}

	printf("using calibration file: %s\n", _calibFile);

	if ((_imageSource == NULL) && (_filename2 != NULL))
	{
		printf("using rgb images: %s\nusing depth images: %s\n", _filename1, _filename2);
		if (_imuFile == NULL)
		{
			ImageMaskPathGenerator pathGenerator(_filename1, _filename2);
			_imageSource = new ImageFileReader<ImageMaskPathGenerator>(_calibFile, pathGenerator);
		}
		else
		{
			printf("using imu data: %s\n", _imuFile);
			_imageSource = new RawFileReader(_calibFile, _filename1, _filename2, Vector2i(320, 240), 0.5f);
			_imuSource = new IMUSourceEngine(_imuFile);
		}

		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			if (_imuSource != NULL) delete _imuSource;
			_imuSource = NULL;
			_imageSource = NULL;
		}
	}

	if ((_imageSource == NULL) && (_filename1 != NULL) && (_imuFile == NULL))
	{
		_imageSource = new InputSource::FFMPEGReader(_calibFile, _filename1, _filename2);
		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			_imageSource = NULL;
		}
	}

	if (_imageSource == NULL)
	{
		// If no calibration file specified, use the factory default calibration
		bool useInternalCalibration = !_calibFile || strlen(_calibFile) == 0;

		printf("trying OpenNI device: %s - calibration: %s\n",
			_filename1 ? _filename1 : "<OpenNI default device>",
			useInternalCalibration ? "internal" : "from file");
		_imageSource = new OpenNIEngine(_calibFile, _filename1, useInternalCalibration);
		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			_imageSource = NULL;
		}
	}

	if (_imageSource == NULL)
	{
		printf("trying UVC device\n");
		_imageSource = new LibUVCEngine(_calibFile);
		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			_imageSource = NULL;
		}
	}

	if (_imageSource == NULL)
	{
		printf("trying RealSense device\n");
		_imageSource = new RealSenseEngine(_calibFile);
		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			_imageSource = NULL;
		}
	}

	/*
	if (_imageSource == NULL)
	{
		printf("trying MS Kinect 2 device\n");
		_imageSource = new Kinect2Engine(_calibFile);
		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			_imageSource = NULL;
		}
	}*/

	if (_imageSource == NULL)
	{
		printf("trying PMD PicoFlexx device\n");
		_imageSource = new PicoFlexxEngine(_calibFile, _subject);
		if (_imageSource->getDepthImageSize().x == 0)
		{
			delete _imageSource;
			_imageSource = NULL;
		}
	}
}