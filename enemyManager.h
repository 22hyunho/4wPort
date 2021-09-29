#pragma once
#include "Enemy.h"
#include "Boss.h"

class Player;

class enemyManager
{
private :
	typedef vector<Enemy*>				_enemyList;
	typedef vector<Enemy*>::iterator	_enemyIter;

	typedef vector<Boss*>				_bossList;
	typedef vector<Boss*>::iterator		_bossIter;

private :
	_enemyList _vEnemy;
	_enemyIter _viEnemy;

	_bossList  _vBoss;
	_bossIter  _viBoss;

	Player* _player;

public :
	enemyManager() {};
	~enemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setEnemy(int num, float x, float y, Player* player);
	void setStage0_1();
	void setBoss(int num, float x, float y, Player* player);

	//=====================접근자&설정자=====================

	_enemyList getVEnemy() { return _vEnemy; }
	_enemyIter getVIEnemy() { return _viEnemy; }

	_bossList getVBoss() { return _vBoss; }
	_bossIter getVIBoss() { return _viBoss; }
};

