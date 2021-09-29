#include "stdafx.h"
#include "Pattern_pathFinder.h"
#include "Player.h"
#include "Enemy.h"

HRESULT Pattern_pathFinder::init(Player * player)
{
	Pattern::init(player);
	return S_OK;
}

HRESULT Pattern_pathFinder::init(Enemy * enemy)
{
	Pattern::init(enemy);
	if (!_pathFinder) {
		_pathFinder = new PathFinder;
		_pathFinder->init();
	}
	_pathFinder->resetPathList();
	return S_OK;
}

void Pattern_pathFinder::release()
{
}

void Pattern_pathFinder::update()
{
	//저장된 경로가 없으면 새로 길 찾기
	
		
	//에너미의 탐지렉트에 플레이어가 들어왔으면
	//패스파인더가 찾은 경로 첫번째 타일로 계속해서 이동한다
	if (COLLISIONMANAGER->attackingPlayer(_enemy, _player))
	{
		if (_enemy->getState() != ES_HURT && _enemy->getState() != ES_DIE && !_enemy->getCoolDown())
		{
			if (_enemy->getState() == ES_ATTACK) return;
			_enemy->changeState(ES_ATTACK);
		}
	}

	else if (COLLISIONMANAGER->detectionPlayer(_enemy, _player) || _enemy->getTrace())
	{
		_pathFinder->setTiles(_enemy, _player);
		_pathFinder->update();
		_pathList = _pathFinder->getPathList();

		_enemy->setEndX((float)_pathList[0]->getIdX() * TILESIZE + TILESIZE * 0.5f);
		_enemy->setEndY((float)_pathList[0]->getIdY() * TILESIZE + TILESIZE * 0.5f);

		if (_enemy->getState() != ES_HURT && _enemy->getState() != ES_DIE && _enemy->getState() != ES_ATTACK)
		{
			if (_enemy->getState() == ES_MOVE) return;
			_enemy->changeState(ES_MOVE);
		}
	}

	else
	{
		if (_enemy->getState() != ES_HURT && _enemy->getState() != ES_DIE && _enemy->getState() != ES_ATTACK)
		{
			if (_enemy->getState() == ES_IDLE) return;
			_enemy->changeState(ES_IDLE);
		}
	}
}

void Pattern_pathFinder::render()
{
	//WCHAR str[128];
	//swprintf_s(str, L"state : %d", _enemy->getState());
	//DTDMANAGER->printText(str, _enemy->getX(), _enemy->getY() - 70, 150, 20);
	//for (int i = 0; i < _pathList.size(); i++)
	//DTDMANAGER->Rectangle(_pathList[i]->getRect());

	//if (_pathList.size() != 0)
	//{
	//	swprintf_s(str, L"p.x : %d p.y : %d", _pathList[0]->getIdX(), _pathList[0]->getIdY());
	//	DTDMANAGER->printText(str, _player->getX(), _player->getY() + 50, 150, 20);
	//}
	//swprintf_s(str, L"e.x : %d e.y : %d", (int)_enemy->getX(), (int)_enemy->getY());
	//DTDMANAGER->printText(str, 100, 260, 150, 20);
}

void Pattern_pathFinder::detour()
{
}
