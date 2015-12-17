#ifndef _PlayerState_H_
#define _PlayerState_H_

#include "State.h"
#include "Player.h"

enum PlayerState
{
	S_ChopDownTree = 0,
	S_DigIronState = 1,
	S_Fight = 2,
};

class ChopDownTreesState :public State < Player* >
{
public:
	virtual void execute(Player*);
	virtual void enter(Player*);
	virtual void exit(Player*);
	virtual int getType(){ return S_ChopDownTree; };
};

class DigIronState :public State < Player* >
{
public:
	virtual void execute(Player*);
	virtual void enter(Player*);
	virtual void exit(Player*);
	virtual int getType(){ return S_DigIronState; };
};

class FightState :public State < Player* >
{
public:
	virtual void execute(Player*);
	virtual void enter(Player*);
	virtual void exit(Player*);
	virtual int getType(){ return S_Fight; };
};

#endif