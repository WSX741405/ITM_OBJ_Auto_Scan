#pragma once

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
#include <QtWidgets/QMainWindow>
#include <QVTKWidget.h>

//		ITM Library
#include "../../../InputSource/include/OpenNIEngine.h"
#include "../../../InputSource/include/Kinect2Engine.h"
#include "../../../InputSource/include/LibUVCEngine.h"
#include "../../../InputSource/include/PicoFlexxEngine.h"
#include "../../../InputSource/include/RealSenseEngine.h"
#include "../../../InputSource/include/LibUVCEngine.h"
#include "../../../InputSource/include/FFMPEGReader.h"
#include "../../../ITMLib/include/ITMLibDefines.h"
#include "../../../ITMLib/include/Core/ITMBasicEngine.h"
#include "../../../ITMLib/include/Core/ITMBasicSurfelEngine.h"
#include "../../../ITMLib/include/Core/ITMMultiEngine.h"

#include "ui_ITM_OBJ_Auto_SCAN.h"
#include "UI/Viewer.h"
#include "ITM/ITMEngine.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	//ITM_OBJ_Auto_SCAN(QWidget *parent = Q_NULLPTR);

private:
	void InitialPointCloudViewer();

	Viewer* _viewer;
	ITMEngine* _engine;
	Ui::OBJMainWindow _ui;
};
