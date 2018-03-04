#ifndef OBSERVER_FACTORY
#define OBSERVER_FACTORY

#include "Observer/Observer.h"

class ISubject;

class SubjectFactory
{
public:
	SubjectFactory()
	{
	}

	ISubject* GetGrabberSubject();
};

#endif