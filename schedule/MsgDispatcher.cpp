#include "stdafx.h"
#include "MsgDispatcher.h"

MsgDispatcher* MsgDispatcher::_msgDispatcher = NULL;

MsgDispatcher::MsgDispatcher()
{

}

MsgDispatcher::~MsgDispatcher()
{

}

void MsgDispatcher::registerObject(Object* obj)
{
	objMap[obj->getId()] = obj;
}

void MsgDispatcher::removeObject(Object* obj)
{
	objMap.erase(obj->getId());
}

MsgDispatcher* MsgDispatcher::getInstance()
{
	if (_msgDispatcher == NULL)
	{
		_msgDispatcher = new MsgDispatcher();
	}
	return _msgDispatcher;
}

void MsgDispatcher::sendMessage(Object* _sender, Object* _reciver, const std::string& _msg, float _delay)
{
	_sender->scheduleOnce(function_selectorN([=](float){
		_reciver->reciveMessage(_sender, _msg);
	}, "Message"), _delay);
}

void MsgDispatcher::sendMessage(Object* _sender, const std::string& _msg, float _delay)
{
	for (auto &obj : objMap)
	{
		if (obj.second->isRegisterMsg(_msg) && obj.second != _sender)
		{
			_sender->scheduleOnce(function_selectorN([=](float){
				obj.second->reciveMessage(_sender, _msg);
			}, "Message"), _delay);
		}
	}
}