#include "UI/ITMEngine.h"

void ITMEngine::SetGrabberSubject(ISubject* subject)
{
	_subject = subject;
}

void ITMEngine::StartProcessing()
{
	CreateImageSource();
}

void ITMEngine::ProcessFrame()
{

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