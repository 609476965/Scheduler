#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(const string& _name)
{
	name = _name;
}

Enemy::~Enemy()
{

}

void Enemy::init(float _attack, float _defence, float _hp, float _ex)
{
	attack = _attack;
	defence = _defence;
	hp = _hp;
	ex = _ex;
	bindFightCallback();
}

void Enemy::bindFightCallback()
{
	bindMsgCallback("attackEnemy", [=](Object* _py){
		auto py = static_cast<Player*>(_py);
		hp -= py->attack;
		if (hp <= 0)
		{
			cout << name << " dead." << endl << endl;
			sendMessage(_py, "playerWin", 2.5);
			scheduleOnce(function_selector([=](float){
				this->isChangeTimerVec = true;
				this->~Enemy();
			}), 5);
			return;
		}
		else
		{
			cout << name << " strike back." << endl;
			cout << py->name << "'s hp deccrese by " << attack - py->defence << "." << endl << endl;
			sendMessage(_py, "attackPlayer", 2.5);
			return;
		}
	});
}