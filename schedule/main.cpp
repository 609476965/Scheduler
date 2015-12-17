// schedule.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Scheduler.h"
#include "Director.h"
#include "MainScene.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Director* director = Director::getInstance();
	director->runWithScene(MainScene::create());
	director->mainLoop();
	return 0;
}

