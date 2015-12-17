#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "MainScene.h"
#include "PlayerState.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

bool MainScene::init()            
{		
	player = new Player("Jack");
	// You can choose 1 - 6;
	test(6);
	return true;
}

void MainScene::test(int type)
{
	switch (type)
	{
	case 1:
		// Test_1
		player->schedule(schedule_selector(Player::toChopDownTrees), 0.5, 1, 5);
		player->schedule(function_selector([=](float){
			player->toDigIron(0);
		}), 0.5, 6, 5);
		break;
	
	case 2:
		// Test_2
		player->scheduleOnce(schedule_selector(Player::toDigIron), 4);
		player->scheduleOnce(function_selector([](float){ cout << "ScheduleOnce lambda function." << endl; }), 6);
		break;
	
	case 3:
		// Test_3
		player->schedule(function_selectorN([](float){ cout << "Follow me, son " << endl; }, "fun"), 1, 1, 5);
		player->scheduleAfter("fun", function_selectorN([](float){ cout << "I'm following" << endl; }, "follow"), 1, 0, 1);
		player->scheduleAfter("follow", function_selector([](float){ cout << "Me too." << endl; }), 1, 0, 1);
		break;
	
	case 4:
		// Test_4
		player->schedule(function_selectorN([](float){ cout << "stop me, please" << endl; }, "stop"), 0.6, 0.5, -1);
		player->unschedule("stop", 5);
		break;
	
	case 5:
		// Test_5
	{
		Object* ftd = new Object();
		ftd->bindMsgCallback("testMsg", [](Object*){ cout << "FTD: I have recived the msg." << endl; });
		player->sendMessage(ftd, "testMsg", 3.5);
		break;
	}

	case 6:
		// Test_6
		player->changeState(new ChopDownTreesState());
		bindCreateEnemyCallback();
		sendMessage(this, "createEnemy", 16);
		break;

	default:
		cout << "just nothing except 1 - 6" << endl;
		break;
	}
}


void MainScene::bindCreateEnemyCallback()
{
	bindMsgCallback("createEnemy", [=](Object*){
		int rd = rand() % 4 * (player->level - 1);
		auto enemy = new Enemy("wolf");
		enemy->init(3 + rd, 1, 12 + rd, 9);
		enemy->sendMessage(player, "attackPlayer");
	});
}
