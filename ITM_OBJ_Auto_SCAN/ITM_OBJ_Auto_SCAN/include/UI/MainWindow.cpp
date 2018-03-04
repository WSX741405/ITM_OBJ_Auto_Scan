#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	_engine = new ITMEngine();
	_viewer = new Viewer();
	_subjectFactory = new SubjectFactory();
	_uiObserver = new UIObserver(this);
	_ui.setupUi(this);
	InitialConnectSlots();
	InitialPointCloudViewer();
	RegisterObserver();
}

//****************************************************************
//								UI
//						Initial, Update etc
//****************************************************************
void MainWindow::InitialPointCloudViewer()
{
	_ui._cloudQVTKWidget->SetRenderWindow(_viewer->GetRenderWindow());
	_viewer->SetupInteractor(_ui._cloudQVTKWidget->GetInteractor(), _ui._cloudQVTKWidget->GetRenderWindow());
	_ui._cloudQVTKWidget->update();
}

void MainWindow::InitialConnectSlots()
{
	connect(_ui._processFrameAction, SIGNAL(triggered()), this, SLOT(ProcessFrameSlot()));
	connect(this->_uiObserver, SIGNAL(UpdateViewer()), this, SLOT(UpdateViewerSlot()));
}

void MainWindow::RegisterObserver()
{
	ISubject* grabberSubject = _subjectFactory->GetGrabberSubject();
	grabberSubject->RegisterObserver(_uiObserver);
	_engine->SetGrabberSubject(grabberSubject);
}

//****************************************************************
//								Slots
//****************************************************************

void MainWindow::ProcessFrameSlot()
{
	_engine->StartProcessing();
}

void MainWindow::UpdateViewerSlot()
{
	_engine->ProcessFrame();
}