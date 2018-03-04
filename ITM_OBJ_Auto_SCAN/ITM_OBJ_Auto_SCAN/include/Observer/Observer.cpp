#include "Observer/Observer.h"

//		*****************************************************************
//				Observer
//				UI
//		*****************************************************************

void UIObserver::Update()
{
	emit UIObserver::UpdateViewer();
}

//		*****************************************************************
//				Subject
//				Grabber(Flexx, RS)
//		*****************************************************************

void GrabberSubject::RegisterObserver(IObserver* observer)
{
	_observers.push_back(observer);
}

void GrabberSubject::NotifyObservers()
{
	for each (IObserver* observer in _observers)
	{
		observer->Update();
	}
}