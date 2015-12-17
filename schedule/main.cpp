// schedule.cpp : 定义控制台应用程序的入口点。
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

