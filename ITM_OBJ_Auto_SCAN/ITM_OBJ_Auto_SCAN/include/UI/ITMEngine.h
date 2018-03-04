#pragma once

#include<cstdlib>

//		ITM Main Include Library
#include "InputSource/OpenNIEngine.h"
#include "InputSource/Kinect2Engine.h"
#include "InputSource/LibUVCEngine.h"
#include "InputSource/PicoFlexxEngine.h"
#include "InputSource/RealSenseEngine.h"
#include "InputSource/LibUVCEngine.h"
#include "InputSource/FFMPEGReader.h"
#include "../../../ITMLib/include/ITMLibDefines.h"
#include "../../../ITMLib/include/Core/ITMBasicEngine.h"
#include "../../../ITMLib/include/Core/ITMBasicSurfelEngine.h"
#include "../../../ITMLib/include/Core/ITMMultiEngine.h"
//		ITM UI Engine Include Library
#include "InputSource/ImageSourceEngine.h"
#include "InputSource/IMUSourceEngine.h"
#include "InputSource/FFMPEGWriter.h"
#include "../../../ITMLib/include/Core/ITMMainEngine.h"
#include "../../../ITMLib/include/Utils/ITMLibSettings.h"
#include "../../../ORUtils/include/FileUtils.h"
#include "../../../ORUtils/include/NVTimer.h"

#include "Observer/Observer.h"

using namespace InputSource;
using namespace ITMLib;

class ISubject;

class ITMEngine
{
public:
	ITMEngine(char* calibFile = "", char* filename1 = NULL, char* filename2 = NULL, char* imuFile = NULL)
		: _calibFile(calibFile), _filename1(filename1), _filename2(filename2), _imuFile(imuFile)
	{
	}

	void SetGrabberSubject(ISubject* subject);
	void StartProcessing();
	void ProcessFrame();

private:
	void CreateImageSource();

	ImageSourceEngine* _imageSource = NULL;
	IMUSourceEngine* _imuSource = NULL;
	char* _calibFile;
	char* _filename1;
	char* _filename2;
	char* _imuFile;
	ISubject* _subject = NULL;
};