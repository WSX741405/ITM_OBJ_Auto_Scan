#include "OBJMainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	_viewer = new Viewer();
	_ui.setupUi(this);
	InitialPointCloudViewer();
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