#include "stdafx.h"
#include "Plant.h"

HRESULT Plant::init(float x, float y, Player * player)
{
	Enemy::init(x, y, player);
	_type = TY_SPECIAL;
	_currentHP = _maxHP = 30;
	_img = IMAGEMANAGER->addFrameDImage("plant_idle", L"img/enemy/plant/plantPot_idle.png", 144, 66, 6, 2);
	IMAGEMANAGER->addFrameDImage("plant_run", L"img/enemy/plant/plantPot_run.png", 120, 66, 4, 2);

	_rc = RectMakeCenter(_x, _y, 24, 33);
	_speed = 5;

	return S_OK;
}

void Plant::release()
{
}

void Plant::update()
{
	Enemy::update();
	switch (_state)
	{
	case ES_IDLE:
		_img = IMAGEMANAGER->findDImage("plant_idle");
		_individualFrame = 0.1f;
		break;

	case ES_MOVE :
		_img = IMAGEMANAGER->findDImage("plant_run");
		break;
	
	case ES_ATTACK:
		EFFECTMANAGER->addPotExplode(_x, _y, 0, 0);
		_death = true;
		_individualFrame = 0.1f;

		break;

	case ES_HURT:
		_hurtCount++;
		if (_hurtCount > 40)
		{
			_state = ES_IDLE;
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		EFFECTMANAGER->addPotExplode(_x, _y, 0, 0);
		_death = true;
		break;
	}
	_rc = RectMakeCenter(_x, _y, 24, 33);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 3, TILESIZE * 3);
}

void Plant::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY);

	controlFrame();

	if (PRINTMANAGER->isDebug()) DTDMANAGER->Rectangle(_detection);
}

void Plant::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= _individualFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			switch (_state)
			{
			case ES_IDLE:
				_frameX = 0;
				break;

			case ES_MOVE :
				_frameX = 0;
				break;
			}
		}

		else
			_frameX++;

		_count = 0;
	}
}

void Plant::changeState(ENEMYSTATE state)
{
	_state = state;
	_frameX = 0;
}
