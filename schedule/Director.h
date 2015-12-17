#ifndef _Director_H_
#define _Director_H_

#include "Scheduler.h"
#include "MainScene.h"
#include "time.h"

class Director
{
public:
	Director();
	~Director();
	// Singleton object
	static Director* getInstance();
	Scheduler* getScheduler();

	void mainLoop();
	void runWithScene(MainScene*);
private:
	static Director* _director;

	// Caculate time's interval
	float dt;
	clock_t m_lastTime, m_currTime;	
	void deltaUpdate();

	Scheduler* scheduler;	
	MainScene* currScene;
	
};

#endif