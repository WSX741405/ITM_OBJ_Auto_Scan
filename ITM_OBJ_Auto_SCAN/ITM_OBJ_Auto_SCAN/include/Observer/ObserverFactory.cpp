#include "Observer/ObserverFactory.h"

ISubject* SubjectFactory::GetGrabberSubject()
{
	static GrabberSubject* subject = new GrabberSubject();
	return (ISubject*)subject;
}