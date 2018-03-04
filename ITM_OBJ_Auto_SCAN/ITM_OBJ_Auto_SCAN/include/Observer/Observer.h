#pragma once

#include "UI/MainWindow.h"

class MainWindow;

//		*****************************************************************
//				Observer
//				UI, 
//		*****************************************************************

class IObserver
{
public:
	virtual void Update() = 0;
};

class UIObserver : public QObject, public IObserver
{
	Q_OBJECT
public:
	UIObserver(MainWindow* window) : _mainWindow(window){}
	void Update();

signals:
	void UpdateViewer();

private:
	MainWindow* _mainWindow;
};

//		*****************************************************************
//				Subject
//				Grabber, 
//		*****************************************************************

class ISubject
{
public:
	virtual void RegisterObserver(IObserver* observer) = 0;
	virtual void NotifyObservers() = 0;

protected:
	std::vector<IObserver*> _observers;
};

class GrabberSubject : ISubject
{
public:
	void RegisterObserver(IObserver* observer);
	void NotifyObservers();
};