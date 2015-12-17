#ifndef _MsgDispatcher_H_
#define _MsgDispatcher_H_

#include "Object.h"
#include "string"
#include "vector"
#include "map"

using namespace std;
class Object;

class MsgDispatcher
{
public:
	MsgDispatcher();
	~MsgDispatcher();
	static MsgDispatcher* getInstance();

	// Function about Message 
	void sendMessage(Object* sender, Object* reciver, const std::string& msg, float delay = 0);
	void sendMessage(Object* sender, const std::string& msg, float delay = 0);

	void registerObject(Object*);
	void removeObject(Object*);
private:
	static MsgDispatcher* _msgDispatcher;

	// Restore all the object
	map < int, Object* > objMap;
};

#endif