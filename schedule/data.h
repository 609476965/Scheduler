#ifndef _Data_H_
#define _Data_H_

#include "Object.h"
#include "Timer.h"
#include "functional"

class Timer;
class Object;

namespace FTD
{

	typedef void(Object::*SCHEDULE)(float);	

	typedef std::function < void(float) > CALLBACK;

	typedef std::function< void(Object*) > MsgCallback;

	struct SELECTOR
	{
		// attribute
		std::string scheduleName;

		SCHEDULE callback;

		CALLBACK function;

		float delayRemove = 0;

		float delayExcute = 0;

		float interval = 0;

		float m_delta = 0;

		float m_removeDelta = 0;

		int times = 0;

		int count = 0;  // calculate the excute times

		int periority = 0; // decide the excute sequence

		bool isPause = false;

		Object* target = NULL;

		SELECTOR(const std::string& _name, const SCHEDULE& _callback)
		{
			scheduleName = _name;
			callback = _callback;
			function = nullptr;
		}
		SELECTOR(const std::string& _name, const CALLBACK _function)
		{
			scheduleName = _name;
			callback = NULL;
			function = _function;
		}
	};

#define ToString(_TYPE_) #_TYPE_

#define schedule_selector(_TYPE_) new SELECTOR(#_TYPE_, static_cast<SCHEDULE>(&_TYPE_))

#define schedule_selectorN(_TYPE_,_NAME_) new SELECTOR(_NAME_, static_cast<SCHEDULE>(&_TYPE_))

#define function_selector(_TYPE_) new SELECTOR(#_TYPE_, _TYPE_)

#define function_selectorN(_TYPE_,_NAME_) new SELECTOR(_NAME_, _TYPE_)

#define CREATA_FUNC(__TYPE__) static __TYPE__* create() \
	{ \
	__TYPE__ *scene = new __TYPE__(); \
	if (scene && scene->init()) \
		{ \
		return scene; \
		} \
		else \
		{ \
		delete scene; \
		scene = NULL; \
		return NULL; \
		} \
	}
}

#endif