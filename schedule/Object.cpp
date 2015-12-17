#include "stdafx.h"
#include "Object.h"
#include "Director.h"
#include "iostream"
using namespace std;

int Object::idGenerator = 0;

Object::Object()
{
	isRegister = false;
	isChangeTimerVec = false;
	id = idGenerator++;
	MsgDispatcher::getInstance()->registerObject(this);
}

Object::~Object()
{
	MsgDispatcher::getInstance()->removeObject(this);
	Director::getInstance()->getScheduler()->removeObject(this);
}

void Object::schedule(SELECTOR* _selector, float _interval, float _delay, int _times)
{
	Director::getInstance()->getScheduler()->schedule(this, _selector, _interval, _delay, _times);
}

void Object::scheduleOnce(SELECTOR* _selector, float _delay)
{
	Director::getInstance()->getScheduler()->scheduleOnce(this, _selector, _delay);
}

void Object::scheduleAfter(const string keys, SELECTOR* _selector, float _interval, float _delay, int _times)
{
	Director::getInstance()->getScheduler()->scheduleAfter(this, keys, _selector, _interval, _delay, _times);
}

void Object::unschedule(const std::string keys, float _delayRemove)
{
	Director::getInstance()->getScheduler()->unschedule(this, keys, _delayRemove);
}

void Object::schedulePauseAllCallback(float _delay)
{
	Director::getInstance()->getScheduler()->schedulePauseAllCallback(this, _delay);
}

void Object::scheduleResumeAllCallback(float _delay)
{
	Director::getInstance()->getScheduler()->scheduleResumeAllCallback(this, _delay);
}

void Object::update(float dt)
{
	isChangeTimerVec = false;
	for (int i = 0; !isChangeTimerVec && i != timerVec.size(); i++)
	{
		timerVec.at(i)->update(dt);
	}
}

void Object::sendMessage(Object* _reciver, const string& _msg, float _delay)
{
	MsgDispatcher::getInstance()->sendMessage(this, _reciver, _msg, _delay);
}

void Object::sendMessage(const string& _msg, float _delay)
{
	MsgDispatcher::getInstance()->sendMessage(this, _msg, _delay);
}

void Object::reciveMessage(Object* _sender, const string& _msg)
{
	onHandleMsg(_sender, _msg);
}

void Object::onHandleMsg(Object* _sender, const string& msg)
{
	if (isRegisterMsg(msg))
	{
		msgBox[msg](_sender);
	}
}

bool Object::isRegisterMsg(const string& msg)
{
	if (msgBox[msg] != NULL)
		return true;
	else
		return false;
}

void Object::bindMsgCallback(const string& msg, MsgCallback _callback)
{
	msgBox[msg] = _callback;
}