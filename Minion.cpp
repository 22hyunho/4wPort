#include "stdafx.h"
#include "Minion.h"
#include "Player.h"

HRESULT Minion::init(float x, float y, Player * player)
{
	Enemy::init(x, y, player);
	_type = TY_RANGE;
	_currentHP = _maxHP = 60;
	_img = IMAGEMANAGER->addFrameDImage("minion_idle", L"img/enemy/minionBeholder/minion_idle.png", 189, 114, 3, 2);
	IMAGEMANAGER->addFrameDImage("minion_attack", L"img/enemy/minionBeholder/minion_attack.png", 189, 114, 3, 2);
	IMAGEMANAGER->addFrameDImage("minion_die", L"img/enemy/minionBeholder/minion_die.png", 51, 114, 1, 2);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_detection = RectMakeCenter(_x, _y, TILESIZE * 30, TILESIZE * 20);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_speed = 3;
	_coolDown = false;
	_coolDownCount = 0;

	_plasma = new PlasmaBall;
	_plasma->init(400, 10);
	return S_OK;
}

void Minion::release()
{
}

void Minion::update()
{
	Enemy::update();
	_plasma->update();
	switch (_state)		//idle, move, hurt는 에너미 공동
	{
	case ES_IDLE :
		_x = _x; _y = _y;
		break;

	case ES_ATTACK:
		if (_coolDown)
			changeState(ES_IDLE);

		else
		{
			_attackCount++;

			if (_attackCount > 40)
			{
				_plasma->fire(_x, _y, getAngle(_x, _y, _player->getX(), _player->getY()));
				_coolDown = true;
				_attackCount = 0;
			}
		}
		break;

	case ES_HURT:
		_hurtCount++;
		if (_hurtCount > 30)
		{
			changeState(ES_IDLE);
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		_dieCount++;
		if (_dieCount > 120)
		{
			_death = true;
		}
		break;
	}

	if (_coolDown)
	{
		_coolDownCount++;
		if (_coolDownCount > 30)
		{
			_coolDown = false;
			_coolDownCount = 0;
		}
	}
	_rc = RectMakeCenter(_x, _y, 48, 48);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 30, TILESIZE * 20);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 5, TILESIZE * 5);
}

void Minion::render()
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
	_plasma->render();
}

void Minion::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= 0.1f)
	{
		if (_frameX >= _img->getMaxFrameX())
			_frameX = 0;

		else
			_frameX++;

		_count = 0;
	}
}

void Minion::changeState(ENEMYSTATE state)
{
	_state = state;
	switch (_state)
	{
	case ES_IDLE :
		_img = IMAGEMANAGER->findDImage("minion_idle");
		_frameX = 0;
		break;

	case ES_ATTACK :
		_img = IMAGEMANAGER->findDImage("minion_attack");
		_frameX = 0;
		break;

	case ES_DIE :
		_img = IMAGEMANAGER->findDImage("minion_die");
		break;
	}
}
