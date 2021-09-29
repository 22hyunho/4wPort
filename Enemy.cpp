#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Pattern_default.h"
#include "Pattern_pathFinder.h"

HRESULT Enemy::init(float x, float y, Player * player)
{
	_x = x;
	_y = y;
	_z = 1;
	_endX = _x + 10;
	_endY = _y;
	_count = _attackCount = _hurtCount = _dieCount = 0;
	_frameX = _frameY = 0;
	_tuningX = _tuningY = 0;
	_knockBack = 2.5f;
	_gravity = 0.02f;
	_state = ES_IDLE;

	_death = false;
	_trace = false;
	_traceCount = 0;

	_player = player;

	_pattern[PT_DEFAULT] = new Pattern_default;
	_pattern[PT_PATHFIND] = new Pattern_pathFinder;
	changePattern(PT_PATHFIND);
	return S_OK;
}

void Enemy::update()
{
	if (_state != ES_HURT)
		_knockBack = 2.5f;

	if (_type != TY_SPECIAL && _state == ES_DIE)
	{

		_dieCount++;
		if (_dieCount > 120)
		{
			int rnd = 0;
			int rnd2 = 0;
			rnd = RND->getFromIntTo(1, 101);
			rnd2 = RND->getInt(3);

			if (rnd > 60 && rnd2 == 0)
				ITEMMANAGER->dropRune(_x, _y, 0, RND->getFromIntTo(1, 5));

			else if (rnd > 60 && rnd2 == 1)
			{
				if (!_player->getChance())
					ITEMMANAGER->dropGold(_x, _y, 0, RND->getFromFloatTo(1, 5));
				else
					ITEMMANAGER->dropGold(_x, _y, 0, RND->getFromFloatTo(5, 11));
			}

			else if (rnd > 60 && rnd2 == 2)
				ITEMMANAGER->dropMeat(_x, _y, 0, 0);
			_death = true;
		}
	}

	COLLISIONMANAGER->enemyWithTile(this);

	switch (_state)
	{

	case ES_MOVE:
		move();
		break;

	case ES_HURT :
		knockBack();
		_trace = true;
		break;
	}

	if (_trace)
	{
		_traceCount++;

		if (_traceCount > 180)
		{
			_traceCount = 0;
			_trace = false;
		}
	}

	if (_state != ES_DIE)
	{
		if (_x < _endX) _frameY = 0;
		else			_frameY = 1;
	}

	_pattern[PT_PATHFIND]->update();
	
}

void Enemy::move()
{
	_x += cosf(getAngle(_x, _y, _endX, _endY)) * _speed;
	_y += -sinf(getAngle(_x, _y, _endX, _endY)) * _speed;
}

void Enemy::knockBack()
{
	_x += cosf(_kAngle) * (_knockBack -= _gravity);
	_y += -sinf(_kAngle) * (_knockBack -= _gravity);
}

void Enemy::knockBack(float angle)
{
	_kAngle = angle;
}

void Enemy::changePattern(ENEMYPATTERN pattern)
{
	if (_currentPattern == pattern) return;

	_currentPattern = pattern;
	_pattern[_currentPattern]->init(this);
	_pattern[_currentPattern]->init(_player);
}

void Enemy::changeHP(int damage)
{
	_currentHP -= damage;
}
