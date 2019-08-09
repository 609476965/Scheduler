#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
{
	isSeltChange = false;
}

void Timer::bindObjectAndSelector(Object* _target, SELECTOR* _selector)
{
	_selector->target = _target;
	_selector->periority = 0;
	selector.push_back(_selector);
}

void Timer::initAttr(SELECTOR* _selector, float _interval, float _delay, int _times)
{
	_interval < 0 ? _selector->interval = 0 : _selector->interval = _interval;
	_delay < 0 ? _selector->delayExcute = 0 : _selector->delayExcute = _delay;
	_times < -1 ? _selector->times = -1 : _selector->times = _times;
}

void Timer::setDelayRemove(SELECTOR* _selector, float _delayRemove)
{
	_selector->m_removeDelta = 0;
	_selector->delayRemove = _delayRemove;
}


void Timer::update(float dt)
{
	isSeltChange = false;
	int _periority = selector.front()->periority;
	for (int index = 0; !isSeltChange && index != selector.size(); index++)
	{
		if (selector.size() <= 0) {
			break;
		}
		SELECTOR* selt = selector.at(index);
		if (selt->periority != _periority)
		{
			return;
		}
		else
		{
			if (selt->isPause)
			{
				continue;
			}
			selt->m_delta += dt;
			if (selt->delayRemove > 0)
			{
				selt->m_removeDelta += dt;
			}
			if (selt->count >= selt->times && selt->times != -1 ||
				(selt->delayRemove != 0 && selt->m_removeDelta >= selt->delayRemove))
			{
				selt->target->unschedule(selt->scheduleName);
				continue;
			}
			if (selt->delayExcute != 0 && selt->m_delta >= selt->delayExcute)
			{
				selt->delayExcute = 0;
				selt->m_delta = 0;
				selt->count++;
				if (selt->callback != NULL)
					(selt->target->*selt->callback)(dt);
				else
				{
					selt->function(dt);
				}
				continue;
			}
			if (selt->m_delta >= selt->interval && selt->times == -1 && selt->delayExcute == 0)
			{
				selt->m_delta = 0;
				if (selt->callback != NULL)
					(selt->target->*selt->callback)(dt);
				else
				{
					selt->function(dt);
				}
				continue;
			}
			if (selt->m_delta >= selt->interval && selt->delayExcute == 0)
			{
				selt->m_delta = 0;
				selt->count++;
				if (selt->callback != NULL)
					(selt->target->*selt->callback)(dt);
				else
				{
					selt->function(dt);
				}
				continue;
			}
		}
	}
}