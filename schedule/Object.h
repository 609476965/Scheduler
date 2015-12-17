#ifndef _Object_H_
#define _Object_H_

#include "Timer.h"
#include "MsgDispatcher.h"
#include "vector"
#include "map"
#include "string"
#include "data.h"

class Timer;
using namespace std;
using namespace FTD;

class Object
{
public:
	// Initialize
	Object();
	virtual ~Object();

	// Control variable
	bool isRegister;
	bool isChangeTimerVec;
	std::vector<Timer*> timerVec;
	int getId(){ return id; };

	// Schedule function
	void schedule(SELECTOR*, float interval = 0.15, float delay = 0, int times = -1);
	void scheduleOnce(SELECTOR*, float delay = 0);
	void scheduleAfter(const std::string keys, SELECTOR*, float interval = 0.15, float delay = 0, int times = -1);
	void unschedule(const std::string keys, float delay = 0);
	void schedulePauseAllCallback(float delay = 0);
	void scheduleResumeAllCallback(float delay = 0);

	// Message function
	void sendMessage(Object* reciver, const string& msg, float delay = 0);
	void sendMessage(const string& msg, float delay = 0);
	void reciveMessage(Object* sender, const string& msg);
	void bindMsgCallback(const string& msg, MsgCallback);
	bool isRegisterMsg(const string& msg);

	// Update function
	virtual void update(float);

protected:
	// Identifies
	static int idGenerator;
	int id;

	// Restore the message callback function
	map <string, MsgCallback> msgBox;

	// Handle the message
	void onHandleMsg(Object* sender, const string& msg);

};

#endif