#ifndef _Scheduler_H_
#define _Scheduler_H_

#include "Object.h"

class Scheduler
{
public:
	// Initialize
	Scheduler();
	~Scheduler();

	// To avoid out of the range
	bool isChangeObjMap;

	void update(float);

	// Schedule function
	void schedule(Object*, SELECTOR*, float interval = 0.15, float delay = 0, int times = -1);
	void scheduleOnce(Object*, SELECTOR*, float delay = 0);
	void scheduleAfter(Object*, const std::string& keys, SELECTOR*, float interval = 0.15, float delay = 0, int times = -1);
	void unschedule(Object*, const std::string& keys, float delay = 0);
	
	// Pause and resue function
	void schedulePauseAllCallback(Object*, float delay = 0);
	void scheduleResumeAllCallback(Object*, float delay = 0);
	
	// Manage the object
	void registerObject(Object*);
	void removeObject(Object*);

private:
	// To caculate time 
	float m_delta;
	//vector < Object* > objVec;
	map < int, Object* > objMap;

};

#endif