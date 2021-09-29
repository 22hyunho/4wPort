#include "stdafx.h"
#include "Jessica.h"

HRESULT Jessica::init()
{
	Character::init();
	addImage();
	_x = 600;
	_y = 845;
	_z = 1;

	_state = ST_IDLE;
	_img = IMAGEMANAGER->findDImage("jessica_idle");
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
	_interactRc = RectMakeCenter(_x, _y, TILESIZE + 2, TILESIZE + 4);
	_frameX = 0;
	_frameY = 0;
	_hp = 4;
	_damage = 10;
	_index = CH_XBOW;

	_bowCount = _bowFrameX = 0;

	return S_OK;
}

void Jessica::release()
{
}

void Jessica::update()
{
	Character::update();
	switch (_state)
	{
	case ST_IDLE:
		_img = IMAGEMANAGER->findDImage("jessica_idle");
		if (_direct == 0)
			_tuningX = -5;
		else
			_tuningX = -5;
		break;

	case ST_RUN:
		_img = IMAGEMANAGER->findDImage("jessica_run");
		break;

	case ST_SHOOT :
		_img = IMAGEMANAGER->findDImage("jessica_idleShoot");
		if (_direct == 1)
			_tuningX = 7;
		else if (_direct == 0)
			_tuningX = -7;

		_tuningY = 3;
		break;
		
	case ST_MOVINGSHOOT :
		_img = IMAGEMANAGER->findDImage("jessica_runShoot");
		if (_direct == 1)
			_tuningX = 4;
		else if (_direct == 0)
			_tuningX = -4;
		break;

	case ST_DEPLOY :
		_img = IMAGEMANAGER->findDImage("jessica_deploy");
		break;

	case ST_DODGE :
		_img = IMAGEMANAGER->findDImage("jessica_dash");
		break;

	case ST_HURT :
		_img = IMAGEMANAGER->findDImage("jessica_hurt");
		_tuningY = 5;
		break;

	case ST_DIE :
		_img = IMAGEMANAGER->findDImage("jessica_die");
		if (_direct == 0)
			_tuningX = -5;
		break;
	}

	if (_dodge)
	{
		_dodgeCount++;
		if (_dodgeCount > 15)
		{
			_dodge = false;
			_dodgeCount = 0;
			changeState(ST_IDLE);
		}
	}
}

void Jessica::render(float x, float y, float angle)
{
	_img->frameRender(x - TILESIZE / 4 + _tuningX, y - TILESIZE / 2 + _tuningY, _frameX, _frameY, _alpha);
	if (!UIMANAGER->getOpen()) controlFrame();

	_bowX = x + 2;
	_bowY = y + 8;
	_bowRc = RectMakeCenter(_bowX, _bowY, _bow->getFrameWidth(), _bow->getFrameHeight());
	DTDMANAGER->setRotate(TODEGREE(angle) * -1, _bowX, _bowY);
	if (_state == ST_SHOOT || _state == ST_MOVINGSHOOT) _bow->frameRender(_bowRc.left, _bowRc.top, _bowFrameX, 0);
	DTDMANAGER->resetTransform();
	crossbowFrame();
	//DTDMANAGER->setRotate(TODEGREE(_angle) * -1, _x, _y);
	//DTDMANAGER->Rectangle(_bowRc);
}

void Jessica::crossbowFrame()
{
	if (_state == ST_SHOOT || _state == ST_MOVINGSHOOT)
	{
		_bowCount += TIMEMANAGER->getElapsedTime();

		if (_bowCount >= 0.07f)
		{
			if (_bowFrameX >= _bow->getMaxFrameX())
				_bowFrameX = 0;

			else
				_bowFrameX++;

			_bowCount = 0;
		}
	}
}

void Jessica::addImage()
{
	IMAGEMANAGER->addFrameDImage("jessica_idle", L"img/player/xbow_idle.png", 198, 96, 6, 2);
	IMAGEMANAGER->addFrameDImage("jessica_run", L"img/player/xbow_run.png", 240, 96, 8, 2);
	IMAGEMANAGER->addFrameDImage("jessica_idleShoot", L"img/player/xbow_idleShoot.png", 21, 90, 1, 2);
	IMAGEMANAGER->addFrameDImage("jessica_runShoot", L"img/player/xbow_runShoot.png", 192, 96, 8, 2);
	IMAGEMANAGER->addFrameDImage("jessica_deploy", L"img/player/xbow_throw.png", 390, 96, 10, 2);
	IMAGEMANAGER->addFrameDImage("jessica_dash", L"img/player/xbow_dash.png", 36, 60, 1, 2);
	IMAGEMANAGER->addFrameDImage("jessica_hurt", L"img/player/xbow_hurt.png", 30, 84, 1, 2);
	IMAGEMANAGER->addFrameDImage("jessica_die", L"img/player/xbow_die.png", 585, 114, 13, 2);
	_bow = IMAGEMANAGER->addFrameDImage("crossbow", L"img/player/xbow_crossbow.png", 135, 18, 5, 1);
}
