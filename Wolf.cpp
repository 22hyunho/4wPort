#include "stdafx.h"
#include "Wolf.h"
#include "Player.h"

HRESULT Wolf::init(float x, float y, Player* player)
{
	Enemy::init(x, y, player);
	_type = TY_MELEE;
	_currentHP = _maxHP = 60;
	_img = IMAGEMANAGER->addFrameDImage("wolf_idle", L"img/enemy/wolf/wolf_idle.png", 120, 90, 2, 2);
	IMAGEMANAGER->addFrameDImage("wolf_run", L"img/enemy/wolf/wolf_run.png", 522, 96, 6, 2);
	IMAGEMANAGER->addFrameDImage("wolf_attack", L"img/enemy/wolf/wolf_attack.png", 276, 138, 4, 2);
	IMAGEMANAGER->addFrameDImage("wolf_hurt", L"img/enemy/wolf/wolf_hurt.png", 54, 96, 1, 2);
	IMAGEMANAGER->addFrameDImage("wolf_die", L"img/enemy/wolf/wolf_die.png", 81, 72, 1, 2);

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_speed = 4;
	return S_OK;
}

void Wolf::release()
{
}

void Wolf::update()
{
	Enemy::update();

	switch (_state)		//idle, move, hurt는 에너미 공동
	{
	case ES_IDLE:
		_img = IMAGEMANAGER->findDImage("wolf_idle");
		_individualFrame = 0.6f;
		_tuningY = 0;
		break;

	case ES_MOVE:
		_img = IMAGEMANAGER->findDImage("wolf_run");
		_individualFrame = 0.06f;
		_tuningY = 0;
		break;

	case ES_ATTACK:
		_img = IMAGEMANAGER->findDImage("wolf_attack");
		_individualFrame = 0.2f;
		_tuningY = -20;
		if (_coolDown)
			changeState(ES_IDLE);

		else
		{
			if (_frameX < 3)
			EFFECTMANAGER->addNullBox(_x, _y, TILESIZE * 3, TILESIZE * 3);
		}
		break;

	case ES_HURT:
		_img = IMAGEMANAGER->findDImage("wolf_hurt");
		_hurtCount++;
		if (_hurtCount > 50)
		{
			_state = ES_IDLE;
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		_img = IMAGEMANAGER->findDImage("wolf_die");
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
	_rc = RectMakeCenter(_x, _y, 48, 48);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 2, TILESIZE * 2);
}

void Wolf::render()
{
	_img->frameRender(_rc.left + _tuningX, _rc.top + _tuningY, _frameX, _frameY);

	controlFrame();

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_detection);
		DTDMANAGER->Rectangle(_attackBox);
		//WCHAR str[128];
		//swprintf_s(str, L"x : %f y : %f", _x, _y);
		//DTDMANAGER->printText(str, _x, _rc.top - 20, 150, 20);
	}
}

void Wolf::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= _individualFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			switch (_state)
			{
			case ES_IDLE :
				_frameX = 0;
				break;
			case ES_MOVE :
				_frameX = 0;
				break;
			case ES_ATTACK :
				_frameX = 0;
				_coolDown = true;
				break;
			}
		}
		//_frameX = 0;

		else
			_frameX++;

		_count = 0;
	}
}

void Wolf::changeState(ENEMYSTATE state)
{
	_state = state;
	_frameX = 0;
}
