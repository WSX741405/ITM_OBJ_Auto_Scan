#pragma once

#undef max
#undef min

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
#include <QtWidgets/QMainWindow>
#include <QVTKWidget.h>

#include "ui_ITM_OBJ_Auto_SCAN.h"
#include "UI/Viewer.h"
#include "UI/ITMEngine.h"
#include "Observer/ObserverFactory.h"

class ITMEngine;
class UIObserver;
class SubjectFactory;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	//ITM_OBJ_Auto_SCAN(QWidget *parent = Q_NULLPTR);

public slots:
	void ProcessFrameSlot();
	void UpdateViewerSlot();

private:
	void InitialConnectSlots();
	void InitialPointCloudViewer();
	void RegisterObserver();

	ITMEngine* _engine;
	Viewer* _viewer;
	SubjectFactory* _subjectFactory;
	UIObserver* _uiObserver;
	Ui::OBJMainWindow _ui;
};
