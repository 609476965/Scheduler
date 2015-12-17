#include"stdafx.h"
#include "Player.h"
#include "PlayerState.h"
#include "string"
#include "iostream"
#include "Enemy.h"
#include "iomanip"
using namespace std;

Player::Player(std::string _name)
{
	name = _name;
	currState = NULL;
	prevState = NULL;
	// initialize source
	wood = 0;
	gold = 0;
	iron = 0;
	// initialize attribute
	attack = 5;
	defence = 1;
	hp = 10;
	level = 1;
	ex = 0;
	// initialize ability
	chopDownSpeed = 5;
	digIronSpeed = 3;

	// Register message
	onFight();
	onWinFight();
}

Player::~Player()
{

}

void Player::changeState(State<Player*> *state)
{
	if (prevState != NULL)
	{		
		delete prevState;
		prevState = NULL;
	}		
	if (currState != NULL)
	{
		prevState = currState;
		currState->exit(this);
	}	
	currState = state;
	currState->enter(this);
	currState->execute(this);
}

void Player::resumeState()
{
	if (prevState != NULL)
	{
		if (currState != NULL)
		{
			currState->exit(this);	
			delete currState;
			currState = NULL;
		}				
		currState = prevState;
		prevState = NULL;
	}
	else
		changeState(new ChopDownTreesState());
}

void Player::levelUp()
{
	ex = 0;
	level += 1;
	attack += 2.4;
	defence += 0.3;
	hp = 10 * level;
	chopDownSpeed += 1.6;
	digIronSpeed += 1.2;
	cout << endl << "  levelUp!" << endl;
	cout << "-------------------------State-------------------------" << endl;
	cout << "    " << left << setw(17) << " attack: " << left << setw(4) << attack << "      ";
	cout << setw(17) << " defence: " << defence << endl;
	cout << "    " << left << setw(17) << " chopDownSpeed: " << left << setw(4) << chopDownSpeed << "      ";
	cout << setw(17) << " digIronSpeed: " << digIronSpeed << endl;
	cout << "    " << left << setw(17) << " level: " << left << setw(4) << level << "      ";
	cout << setw(17) << " hp: " << hp << endl;
	cout << "-------------------------------------------------------" << endl << endl;
}

void Player::toChopDownTrees(float)
{
	wood += chopDownSpeed;
	cout << "add " << chopDownSpeed << " woods." << endl;
	cout << name
		<< "'s woods are " << wood << " now." << endl;
}

void Player::toDigIron(float)
{
	iron += digIronSpeed;
	cout << "add " << digIronSpeed << " irons." << endl;
	cout << name
		<< "'s irons are " << iron << " now." << endl;
	/*if (iron >= 50)
		changeState(new ChopDownTreesState());*/
}

// Msg : attackPlayer
void Player::onFight()
{
	bindMsgCallback("attackPlayer", [=](Object* _enemy){
		if (currState == NULL || currState->getType() != S_Fight)
		{
			changeState(new FightState());			
		}		
		auto enemy = static_cast<Enemy*>(_enemy);
		hp -= enemy->attack - defence;
		if (hp + defence > enemy->attack)
		{
			cout << name << " is hitting back! " << endl;
			cout << enemy->name << " reduce " << attack - enemy->defence << " hp!" << endl << endl;
			sendMessage(_enemy, "attackEnemy", 2.5);
		}
		else
		{
			cout << name << "'s hp is very low." << endl;
			cout << name << " is escaping now...." << endl << endl;
			hp = level * 10;
			scheduleOnce(function_selectorN([=](float){
				cout << name << " go to work again." << endl << endl;
				resumeState();
			}, "Protected"), 2.5);
			sendMessage("createEnemy", 20);
		}
	});
}

// Msg :: playerWin
void Player::onWinFight()
{
	bindMsgCallback("playerWin", [=](Object* _enemy){
		auto enemy = static_cast<Enemy*>(_enemy);
		ex += enemy->ex;
		if (ex >= level * 8)
			levelUp();
		scheduleOnce(function_selectorN([=](float){
			cout << name << " go to work again." << endl << endl;
			resumeState();
			//this->scheduleResumeAllCallback();
		}, "Protected"), 3.5);
		sendMessage("createEnemy", 20);
	});
}