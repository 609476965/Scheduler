#include "stdafx.h"
#include "Scheduler.h"
#include "Director.h"
#include "iostream"
using namespace std;

Scheduler::Scheduler()
{
	m_delta = 0;
	isChangeObjMap = false;
}

Scheduler::~Scheduler()
{

}

void Scheduler::registerObject(Object* obj)
{
	/*objVec.push_back(obj);*/
	objMap[obj->getId()] = obj;
}

void Scheduler::removeObject(Object* obj)
{
	/*for (int i = 0; i != objVec.size(); i++)
	{
	if (objVec.at(i) == obj)
	{
	isChangeObjVec = true;
	objVec.erase(objVec.begin() + i);
	break;
	}
	}*/
	isChangeObjMap = true;
	objMap.erase(obj->getId());
}

void Scheduler::update(float dt)
{
	/*if (objVec.empty())
	{
		return;
	}
	isChangeObjVec = false;
	for (int i = 0; !isChangeObjVec && i != objVec.size(); i++)
	{
		objVec.at(i)->update(dt);
	}*/
	if (objMap.empty())
	{
		return;
	}
	isChangeObjMap = false;
	for (auto it = objMap.begin(); !isChangeObjMap && it != objMap.end(); it++)
	{
		it->second->update(dt);
	}
}

void Scheduler::schedule(Object* _target, SELECTOR* _selector, float _interval, float _delay, int _times)
{
	Timer* timer = new Timer();
	timer->bindObjectAndSelector(_target, _selector);
	timer->initAttr(_selector, _interval, _delay, _times);
	_target->timerVec.push_back(timer);
	if (!_target->isRegister)
	{
		_target->isRegister = true;
		registerObject(_target);
	}
}

void Scheduler::scheduleAfter(Object* _target, const string& keys, SELECTOR* _selector, float _interval, float _delay, int _times)
{
	for (int i = 0; i != _target->timerVec.size(); i++)
	{
		Timer* timer = _target->timerVec.at(i);
		vector<SELECTOR*>* seltVec = &timer->selector;
		for (int j = 0; j != seltVec->size(); j++)
		{
			SELECTOR* selt = seltVec->at(j);
			if (selt->scheduleName == keys)
			{
				_selector->target = _target;
				_selector->periority = selt->periority + 1;
				timer->initAttr(_selector, _interval, _delay, _times);
				while (1)
				{					
					if (j + 1 >= seltVec->size() || seltVec->at(j + 1)->periority != selt->periority)
						break;
					j++;
				}
				seltVec->insert(seltVec->begin() + j + 1, _selector);
				return;
			}
		}
	}
}

void Scheduler::scheduleOnce(Object* _target, SELECTOR* _selector, float _delay)
{
	Timer* timer = new Timer();
	timer->bindObjectAndSelector(_target, _selector);
	timer->initAttr(_selector, 0, _delay, 1);
	_target->timerVec.push_back(timer);
	if (!_target->isRegister)
	{
		_target->isRegister = true;
		registerObject(_target);
	}
}

void Scheduler::unschedule(Object* _target, const std::string& keys, float _delayRemove)
{
	for (int i = 0; i != _target->timerVec.size(); i++)
	{
		Timer* timer = _target->timerVec.at(i);
		SELECTOR* selt = NULL;
		string callbackName;
		if (_delayRemove > 0)
		{
			for (int j = 0; j != timer->selector.size(); j++)
			{
				selt = timer->selector.at(j);
				callbackName = selt->scheduleName;
				if (callbackName == keys)
				{
					timer->setDelayRemove(selt, _delayRemove);
					break;
				}
			}
			return;
		}
		else
		{
			selt = timer->selector.front();
			callbackName = selt->scheduleName;
			if (callbackName == keys)
			{
				if (timer->selector.size() > 1)
				{
					delete selt;
					selt = NULL;
					// Only delete the first item
					timer->selector.erase(timer->selector.begin());
					timer->isSeltChange = true;
					return;
				}
				else
				{
					// Delete the timer
					_target->timerVec.erase(_target->timerVec.begin() + i);
					delete timer;
					_target->isChangeTimerVec = true;
					break;
				}
			}
		}
	}
		if (_target->timerVec.size() == 0)
		{
			removeObject(_target);
			_target->isRegister = false;
		}
}

void Scheduler::schedulePauseAllCallback(Object* _target, float _delay)
{
	scheduleOnce(_target, function_selector([=](float){
	for (int i = 0; i != _target->timerVec.size(); i++)
	{
		Timer* timer = _target->timerVec.at(i);
		auto seltVec = timer->selector;
		for (int j = 0; j != seltVec.size(); j++)
		{
			SELECTOR* selt = seltVec.at(j);
			if (selt->scheduleName != "Protected" && selt->scheduleName != "Message")
			{
				selt->isPause = true;
			}
		}
	}
	}), _delay);

}

void Scheduler::scheduleResumeAllCallback(Object* _target, float _delay)
{
	scheduleOnce(_target, function_selectorN([=](float){
	for (int i = 0; i != _target->timerVec.size(); i++)
	{
		Timer* timer = _target->timerVec.at(i);
		auto seltVec = timer->selector;
		for (int j = 0; j != seltVec.size(); j++)
		{
			SELECTOR* selt = seltVec.at(j);
			selt->isPause = false;
		}
	}
	}, "Protected"), _delay);
	
}