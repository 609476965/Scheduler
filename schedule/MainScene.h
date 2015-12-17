#ifndef _MainScene_H_
#define _MainScene_H_

#include "data.h"
#include "Object.h"
#include "Player.h"
using namespace FTD;

class MainScene :public Object
{
public:
	MainScene();
	~MainScene();
	CREATA_FUNC(MainScene);
private:
	virtual bool init();
	void bindCreateEnemyCallback();
	void test(int);
	Player* player;
};

#endif