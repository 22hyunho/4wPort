#include "stdafx.h"
#include "Bat.h"
#include "Player.h"

HRESULT Bat::init(float x, float y, Player* player)
{
	Enemy::init(x, y, player);
	_type = TY_MELEE;
	_currentHP = _maxHP = 30;
	_img = IMAGEMANAGER->addFrameDImage("bat_idle", L"img/enemy/bat/bat_idle.png", 294, 72, 7, 2);
	IMAGEMANAGER->addFrameDImage("bat_attack", L"img/enemy/bat/bat_attack.png", 1008, 168, 12, 2);
	IMAGEMANAGER->addFrameDImage("bat_hurt", L"img/enemy/bat/bat_hurt.png", 54, 54, 1, 2);
	IMAGEMANAGER->addFrameDImage("bat_die", L"img/enemy/bat/bat_die.png", 108, 60, 2, 2);

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_speed = 4;
	return S_OK;
}

void Bat::release()
{
}

void Bat::update()
{
	Enemy::update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_detection = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 2, TILESIZE * 2);

	switch (_state)
	{
	case ES_IDLE:
		_img = IMAGEMANAGER->findDImage("bat_idle");
		_individualFrame = 0.06f;
		break;

	case ES_MOVE:
		_img = IMAGEMANAGER->findDImage("bat_idle");
		_individualFrame = 0.06f;
		break;

	case ES_ATTACK:
		_img = IMAGEMANAGER->findDImage("bat_attack");
		_individualFrame = 0.06f;
		if (_coolDown)
			changeState(ES_IDLE);

		else
		{
			if (_frameX < 3)
			EFFECTMANAGER->addNullBox(_x, _y, TILESIZE * 3, TILESIZE * 3);
		}
		break;

	case ES_HURT:
		_img = IMAGEMANAGER->findDImage("bat_hurt");
		_hurtCount++;
		if (_hurtCount > 50)
		{
			_state = ES_IDLE;
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		_img = IMAGEMANAGER->findDImage("bat_die");
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
}

void Bat::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY);

	controlFrame();

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_detection);
		DTDMANAGER->Rectangle(_attackBox);
		WCHAR str[128];
		//swprintf_s(str, L"x : %f y : %f", _x, _y);
		//DTDMANAGER->printText(str, _x, _rc.top - 20, 150, 20);
		swprintf_s(str, L"endX : %f endY : %f", _endX, _endY);
		DTDMANAGER->printText(str, 200, 600, 150, 20);
	}
}

void Bat::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= _individualFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
			switch (_state)
			{
			case ES_IDLE :
				_frameX = 0;
				break;

			case ES_MOVE :
				_frameX = 0;
				break;

			case ES_ATTACK :
				_frameX = _img->getMaxFrameX();
				_coolDown = true;
				break;

			case ES_HURT :
				_frameX = _img->getMaxFrameX();
				break;

			case ES_DIE :
				_frameX = _img->getMaxFrameX();
				break;
			}

		else
			_frameX++;

		_count = 0;
	}
}

void Bat::changeState(ENEMYSTATE state)
{
	_frameX = 0;
	_state = state;
}
