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
	//objVec.push_back(obj);
	objMap[obj->getId()] = obj;
}

void MsgDispatcher::removeObject(Object* obj)
{
	/*for (int i = 0; i != objVec.size(); i++)
	{
	if (objVec.at(i) == obj)
	{
	objVec.erase(objVec.begin() + i);
	break;
	}
	}*/
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
	/*for (auto obj : objVec)
	{
		if (obj->isRegisterMsg(_msg) && obj != _sender)
		{
			_sender->scheduleOnce(function_selectorN([=](float){
				obj->reciveMessage(_sender, _msg);
			}, "Message"), _delay);
		}
	}*/
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