#ifndef _Player_H_
#define _Player_H_

#include "Object.h"
#include "iostream"
#include "State.h"

class Player :public Object
{
public:
	Player(std::string);
	~Player();

	// Point to state
	State<Player*> *currState;	
	State<Player*> *prevState;

	void changeState(State<Player*>*);
	void resumeState();
	std::string getName(){ return name; };

	// Action function
	void toChopDownTrees(float);
	void toDigIron(float);
	void levelUp();

	// List of source
	float wood;
	float gold;
	float iron;

	// attribute of player
	std::string name;
	float attack;
	float defence;
	float hp;
	float level;
	float ex;

	// ability
	float chopDownSpeed;
	float digIronSpeed;

private:
	// Handle message function
	void onFight();
	void onWinFight();
};

#endif