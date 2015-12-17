#include "stdafx.h"
#include "Director.h"
#include "Scheduler.h"
#include "Player.h"

Director* Director::_director = NULL;

Director::Director()
{
	scheduler = new Scheduler();
}

Director::~Director()
{
	delete scheduler;
	scheduler = NULL;
}

Director* Director::getInstance()
{
	if (_director == NULL)
	{
		_director = new Director();
	}
	return _director;
}

Scheduler* Director::getScheduler()
{
	return scheduler;
}

void Director::deltaUpdate()
{
	m_currTime = clock();
	dt = (float)(m_currTime - m_lastTime) / CLOCKS_PER_SEC;
	m_lastTime = m_currTime;
}

void Director::runWithScene(MainScene* scene)
{
	currScene = scene;
}

void Director::mainLoop()
{
	m_lastTime = clock();
	while (true)
	{
		deltaUpdate();
		scheduler->update(dt);
	}
}

