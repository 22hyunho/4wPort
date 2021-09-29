#include "stdafx.h"
#include "Spider.h"
#include "Player.h"

HRESULT Spider::init(float x, float y, Player * player)
{
	Enemy::init(x, y, player);
	_type = TY_MELEE;
	_currentHP = _maxHP = 40;
	_img = IMAGEMANAGER->addFrameDImage("spider_idle", L"img/enemy/spider/spider_idle.png", 39, 60, 1, 2);
	IMAGEMANAGER->addFrameDImage("spider_run", L"img/enemy/spider/spider_run.png", 180, 60, 4, 2);
	IMAGEMANAGER->addFrameDImage("spider_attack", L"img/enemy/spider/spider_attack.png", 240, 60, 5, 2);
	IMAGEMANAGER->addFrameDImage("spider_hurt", L"img/enemy/spider/spider_hurt.png", 42, 60, 1, 2);
	IMAGEMANAGER->addFrameDImage("spider_die", L"img/enemy/spider/spider_die.png", 48, 60, 1, 2);
	_rc = RectMakeCenter(_x, _y, 39, 30);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 20, TILESIZE * 15);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 2, TILESIZE * 2);
	_speed = 4;
	return S_OK;
}

void Spider::release()
{
}

void Spider::update()
{
	Enemy::update();

	switch (_state)		//idle, move, hurt는 에너미 공동
	{
	case ES_IDLE:
		_img = IMAGEMANAGER->findDImage("spider_idle");
		break;

	case ES_MOVE:
		_img = IMAGEMANAGER->findDImage("spider_run");
		_individualFrame = 0.06f;
		break;

	case ES_ATTACK:
		_img = IMAGEMANAGER->findDImage("spider_attack");
		_individualFrame = 0.1f;
		if (_coolDown)
			changeState(ES_IDLE);

		else
		{
			if (_frameX < 1)
			EFFECTMANAGER->addNullBox(_x, _y, TILESIZE * 3, TILESIZE * 3);
		}
		break;

	case ES_HURT:
		_img = IMAGEMANAGER->findDImage("spider_hurt");
		_hurtCount++;
		if (_hurtCount > 50)
		{
			_state = ES_IDLE;
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		_img = IMAGEMANAGER->findDImage("spider_die");
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
	_rc = RectMakeCenter(_x, _y, 39, 30);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 2, TILESIZE * 2);
}

void Spider::render()
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

void Spider::controlFrame()
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

void Spider::changeState(ENEMYSTATE state)
{
	_state = state;
	_frameX = 0;
}
