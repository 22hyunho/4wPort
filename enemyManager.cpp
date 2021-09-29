#include "stdafx.h"
#include "enemyManager.h"
#include "Bat.h"
#include "Wolf.h"
#include "Plant.h"
#include "Minion.h"
#include "Spider.h"
#include "Orc.h"
#include "OrcWarrior.h"
#include "SpiderQueen.h"
#include "Skeleton.h"
#include "ArmorSkeleton.h"
#include "Boss_beholder.h"
#include "Boss_halfElf.h"

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy) != NULL)
		{
			(*_viEnemy)->release();
			SAFE_DELETE(*_viEnemy);
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else ++_viEnemy;
	}

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end();)
	{
		if ((*_viBoss) != NULL)
		{
			(*_viBoss)->release();
			SAFE_DELETE(*_viBoss);
			_viBoss = _vBoss.erase(_viBoss);
		}
		else ++_viBoss;
	}
}

void enemyManager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->update();
		if ((*_viEnemy)->getDeath())
		{
			SAFE_DELETE(*_viEnemy);
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else ++_viEnemy;
	}

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->update();
	}
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
	
	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->render();
	}
}

void enemyManager::setEnemy(int num, float x, float y, Player* player)
{
	Enemy* enemy;
	enemy = nullptr;
	switch (num)
	{
	case EM_BAT :
		enemy = new Bat;
		break;

	case EM_WOLF :
		enemy = new Wolf;
		break;

	case EM_PLANT :
		enemy = new Plant;
		break;

	case EM_MINION :
		enemy = new Minion;
		break;

	case EM_SPIDER :
		enemy = new Spider;
		break;

	case EM_ORC :
		enemy = new Orc;
		break;

	case EM_ORCWARRIOR :
		enemy = new OrcWarrior;
		break;

	case EM_SPIDERQUEEN :
		enemy = new SpiderQueen;
		break;

	case EM_SKELETON :
		enemy = new Skeleton;
		break;

	case EM_ARMORSKELETON :
		enemy = new ArmorSkeleton;
		break;
	}

	enemy->init(x, y, player);
	_vEnemy.push_back(enemy);
}

void enemyManager::setStage0_1()
{
}

void enemyManager::setBoss(int num, float x, float y, Player* player)
{
	Boss* boss;
	boss = nullptr;
	switch (num)
	{
	case B_BEHOLDER:
		boss = new Boss_beholder;
		break;

	case B_HALFELF :
		boss = new Boss_halfElf;
		break;
	}

	boss->init(x, y, player);
	_vBoss.push_back(boss);
}
