#include "stdafx.h"
#include "Ellis.h"

HRESULT Ellis::init()
{
	Character::init();
	addImage();
	_x = 650;
	_y = 795;
	_z = 1;

	_state = ST_IDLE;
	_img = IMAGEMANAGER->findDImage("ellis_idle");
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
	_interactRc = RectMakeCenter(_x, _y, TILESIZE + 2, TILESIZE + 4);
	_frameX = 0;
	_frameY = 0;
	_hp = 6;
	_damage = 20;
	_index = CH_HUNTER;

	_bowCount = _bowFrameX = _aimFrameX = 0;
	return S_OK;
}

void Ellis::release()
{
}

void Ellis::update()
{
	Character::update();
	switch (_state)
	{
	case ST_IDLE :
		_img = IMAGEMANAGER->findDImage("ellis_idle");
		if (_direct == 1)	_tuningX = -9;
		else				_tuningX = 0;

		break;

	case ST_RUN :
		_img = IMAGEMANAGER->findDImage("ellis_run");
		if (_direct == 1)	_tuningX = -9;
		else				_tuningX = 0;

		break;

	case ST_AIMING :
		_img = IMAGEMANAGER->findDImage("ellis_aiming");
		if (_direct == 1)	_tuningX = -3;
		else				_tuningX = 0;

		break;

	case ST_SHOOT :
		_img = IMAGEMANAGER->findDImage("ellis_shoot");
		if (_direct == 0) _tuningX = -9;
		break;

	case ST_DODGE :
		_img = IMAGEMANAGER->findDImage("ellis_roll");
		if (_direct == 0)
		{
			_tuningX = -15;
			_tuningY = -5;
		}
		else
		{
			_tuningX = -10;
			_tuningY = -5;
		}
		break;

	case ST_DEPLOY :
		_img = IMAGEMANAGER->findDImage("ellis_deploy");
		if (_direct == 0)
		{
			_tuningY = +3;
		}
		else
		{
			_tuningY = +3;
		}
		break;

	case ST_HURT :
		_img = IMAGEMANAGER->findDImage("ellis_hurt");
		if (_direct == 0)
		{
			_tuningY = +5;
		}
		else
		{
			_tuningY = +5;
		}
		break;

	case ST_DIE :
		_img = IMAGEMANAGER->findDImage("ellis_die");
		if (_direct == 0)
		{
			_tuningX = -2;
			_tuningY = +5;
		}
		else
		{
			_tuningX = -34;
			_tuningY = +5;
		}
		break;
	}
}

void Ellis::render(float x, float y, float angle)
{
	_img->frameRender(x - TILESIZE / 4 + _tuningX, y - TILESIZE / 2 + _tuningY, _frameX, _frameY, _alpha);
	if (!UIMANAGER->getOpen()) controlFrame();

	_bowX = x;
	_bowY = y;
	_bowRc = RectMakeCenter(_bowX + 10, _bowY, _bow->getFrameWidth(), _bow->getFrameHeight());
	DTDMANAGER->setRotate(TODEGREE(angle) * -1, _bowX, _bowY);
	if (_state == ST_AIMING) _aim->frameRender(_bowRc.left, _bowRc.top, _aimFrameX, 0);
	else if (_state == ST_SHOOT) _bow->frameRender(_bowRc.left, _bowRc.top, _bowFrameX, 0);
	DTDMANAGER->resetTransform();
	bowFrame();
}

void Ellis::bowFrame()
{
	if (_state == ST_AIMING)
	{
		_bowCount += TIMEMANAGER->getElapsedTime();

		if (_bowCount >= 0.07f)
		{
			if (_aimFrameX >= _aim->getMaxFrameX())
				_aimFrameX = _aim->getMaxFrameX();

			else
				_aimFrameX++;

			_bowCount = 0;
		}
	}
	else
		_aimFrameX = 0;
	if (_state == ST_SHOOT)
	{
		_bowCount += TIMEMANAGER->getElapsedTime();

		if (_bowCount >= 0.07f)
		{
			if (_bowFrameX >= _bow->getMaxFrameX())
				_bowFrameX = _bow->getMaxFrameX();

			else
				_bowFrameX++;

			_bowCount = 0;
		}
	}
	else
		_bowFrameX = 0;
}

void Ellis::addImage()
{
	IMAGEMANAGER->addFrameDImage("ellis_idle", L"img/player/hunter_idle.png", 264, 90, 8, 2);
	IMAGEMANAGER->addFrameDImage("ellis_run", L"img/player/hunter_run.png", 312, 90, 8, 2);
	IMAGEMANAGER->addFrameDImage("ellis_aiming", L"img/player/hunter_aiming.png", 27, 84, 1, 2);
	IMAGEMANAGER->addFrameDImage("ellis_shoot", L"img/player/hunter_shoot.png", 360, 84, 10, 2);
	IMAGEMANAGER->addFrameDImage("ellis_roll", L"img/player/hunter_roll.png", 459, 108, 9, 2);
	IMAGEMANAGER->addFrameDImage("ellis_deploy", L"img/player/hunter_trap.png", 231, 84, 7, 2);
	IMAGEMANAGER->addFrameDImage("ellis_hurt", L"img/player/hunter_hurt.png", 36, 78, 1, 2);
	IMAGEMANAGER->addFrameDImage("ellis_die", L"img/player/hunter_die.png", 567, 84, 9, 2);
	_aim = IMAGEMANAGER->addFrameDImage("bow_aim", L"img/player/bow_aim.png", 36, 30, 3, 1);
	_bow = IMAGEMANAGER->addFrameDImage("bow_shoot", L"img/player/bow_shoot.png", 36, 30, 3, 1);
}
