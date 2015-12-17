#include "stdafx.h"
#include "PlayerState.h"
#include "string"
#include "iostream"
using namespace std;

// Chop down trees
void ChopDownTreesState::enter(Player* player)
{
	cout << player->getName() 
		<< " is chopping down the trees now." << endl << endl;
}

void ChopDownTreesState::execute(Player* player)
{
	player->schedule(schedule_selectorN(Player::toChopDownTrees, "tree"), 1.5, 2.5, 6);
	player->scheduleAfter("tree", function_selector([=](float){
		player->changeState(new DigIronState());
	}), 0, 0, 1);
}

void ChopDownTreesState::exit(Player* player)
{
	//player->unschedule(ToString(Player::toChopDownTrees));
	cout << endl << player->getName()
		<< " leave the logging headquarter." << endl << endl;
}

// Dig iron
void DigIronState::enter(Player* player)
{
	cout << player->getName()
		<< " is digging the iron mine now." << endl << endl;
}

void DigIronState::execute(Player* player)
{
	player->schedule(schedule_selectorN(Player::toDigIron, "iron"), 1.5, 2.5, 6);
	player->scheduleAfter("iron", function_selector([=](float){
		player->changeState(new ChopDownTreesState());
	}), 0, 0, 1);
}

void DigIronState::exit(Player* player)
{
	//player->unschedule(ToString(Player::toDigIron));
	cout << endl << player->getName()
		<< " leave the iron mine." << endl << endl;
}

// Fight
void FightState::enter(Player* player)
{
	cout << player->getName() << " is attacked by enemy!" << endl;
	cout << player->getName()
		<< " is fighting now." << endl << endl;
	player->schedulePauseAllCallback();
}

void FightState::execute(Player* player)
{

}

void FightState::exit(Player* player)
{
	player->scheduleResumeAllCallback();
}