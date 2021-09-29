#include "stdafx.h"
#include "SpiderQueen.h"
#include "Player.h"

HRESULT SpiderQueen::init(float x, float y, Player * player)
{
	Enemy::init(x, y, player);
	_type = TY_MELEE;
	_currentHP = _maxHP = 150;
	_img = IMAGEMANAGER->addFrameDImage("spiderQueen_idle", L"img/enemy/spider/spiderQueen_idle.png", 378, 120, 6, 2);
	IMAGEMANAGER->addFrameDImage("spiderQueen_run", L"img/enemy/spider/spiderQueen_run.png", 264, 120, 4, 2);
	IMAGEMANAGER->addFrameDImage("spiderQueen_attack", L"img/enemy/spider/spiderQueen_attack.png", 525, 120, 7, 2);
	IMAGEMANAGER->addFrameDImage("spiderQueen_hurt", L"img/enemy/spider/spiderQueen_hurt.png", 60, 114, 1, 2);
	IMAGEMANAGER->addFrameDImage("spiderQueen_die", L"img/enemy/spider/spiderQueen_die.png", 66, 108, 1, 2);

	_rc = RectMakeCenter(_x, _y, 63, 60);
	_speed = 3;
	return S_OK;
}

void SpiderQueen::release()
{
}

void SpiderQueen::update()
{
	Enemy::update();

	switch (_state)		//idle, move, hurt는 에너미 공동
	{
	case ES_IDLE:
		_img = IMAGEMANAGER->findDImage("spiderQueen_idle");
		_individualFrame = 0.15f;
		break;

	case ES_MOVE:
		_img = IMAGEMANAGER->findDImage("spiderQueen_run");
		_individualFrame = 0.06f;
		break;

	case ES_ATTACK :
		_img = IMAGEMANAGER->findDImage("spiderQueen_attack");
		_individualFrame = 0.2f;
		if (_coolDown)
			changeState(ES_IDLE);

		else
		{
			if (_frameX < 1)
				EFFECTMANAGER->addNullBox(_x, _y, TILESIZE * 3, TILESIZE * 3);
		}
		break;

	case ES_HURT:
		_img = IMAGEMANAGER->findDImage("spiderQueen_hurt");
		_hurtCount++;
		if (_hurtCount > 50)
		{
			_state = ES_IDLE;
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		_img = IMAGEMANAGER->findDImage("spiderQueen_die");
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
		break;
	}

	if (_coolDown)
	{
		_coolDownCount++;
		if (_coolDownCount > 70)
		{
			_coolDown = false;
			_coolDownCount = 0;
		}
	}
	_rc = RectMakeCenter(_x, _y, 63, 60);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 2, TILESIZE * 2);
}

void SpiderQueen::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY);

	controlFrame();

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_detection);
		DTDMANAGER->Rectangle(_attackBox);
		WCHAR str[128];
		swprintf_s(str, L"x : %f y : %f", _x, _y);
		DTDMANAGER->printText(str, _x, _rc.top - 20, 150, 20);
	}
}

void SpiderQueen::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= _individualFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			if (_state == ES_ATTACK)
				_coolDown = true;

			_frameX = 0;
		}

		else
			_frameX++;

		_count = 0;
	}
}

void SpiderQueen::changeState(ENEMYSTATE state)
{
	_state = state;
	_frameX = 0;
}
