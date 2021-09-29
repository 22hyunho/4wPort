#include "stdafx.h"
#include "Boss_beholder.h"
#include "Player.h"
#include "bossRoom1.h"

HRESULT Boss_beholder::init(float x, float y, Player* player)
{
	Boss::init(x, y, player);
	IMAGEMANAGER->addFrameDImage("beholder_idle", L"img/boss/beholder_idleBody.png", 450, 146, 3, 1);
	IMAGEMANAGER->addFrameDImage("beholder_eye", L"img/boss/beholder_eye.png", 234, 51, 3, 1);
	IMAGEMANAGER->addFrameDImage("beholder_eyeX", L"img/boss/beholder_eyeX.png", 120, 33, 2, 1);
	IMAGEMANAGER->addFrameDImage("beholder_dead", L"img/boss/beholder_dead.png", 312, 147, 2, 1);
	IMAGEMANAGER->addDImage("beholder_attack", L"img/boss/beholder_attackBody.png", 156, 149);
	IMAGEMANAGER->addDImage("beholder_deadFloor", L"img/boss/beholder_deadFloor.png", 135, 129);
	IMAGEMANAGER->addDImage("beholder_hurt", L"img/boss/beholder_hurt.png", 147, 144);

	_bodyFrame = IMAGEMANAGER->findDImage("beholder_idle");
	_eyeFrame = IMAGEMANAGER->findDImage("beholder_eye");
	_rc = RectMakeCenter(_x, _y, 150, 150);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 14, TILESIZE * 20);
	_detection2 = RectMakeCenter(_x, _y, TILESIZE * 30, TILESIZE * 10);
	_eyeFrameX = 0;
	_speed = 0.5f;

	_attackCount = 0;
	_coolDownCount = 0;
	_coolDown = false;
	_death = false;

	_currentHP = _maxHP = 3000;

	_hurtCount = 0;
	_dieCount = 0;
	_tuningDead = 0;

	_plasma = new PlasmaCannon;
	_plasma->init(TILESIZE * 15, 10);

	return S_OK;
}

void Boss_beholder::release()
{
}

void Boss_beholder::update()
{
	_plasma->update();
	detection();
	_rc = RectMakeCenter(_x, _y, 150, 150);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 14, TILESIZE * 20);
	_detection2 = RectMakeCenter(_x, _y, TILESIZE * 30, TILESIZE * 10);
	
	switch (_state)
	{
	case BS_IDLE :
		_x = _x;
		_y = _y;
		_individualFrame = 10;
		if (_x - 30 <= _player->getX() && _x + 30 >= _player->getX()) _eyeFrameX = 0;
		else if (_x + 30 < _player->getX())
			_eyeFrameX = 1;
		
		else
			_eyeFrameX = 2;
		
		break;

	case BS_MOVE :
		_individualFrame = 10;
		_invincible = false;
		if (_x - 30 <= _player->getX() && _x + 30 >= _player->getX()) _eyeFrameX = 0;
		else if (_x + 30 < _player->getX())
		{
			_x += _speed;
			_eyeFrameX = 1;
		}
		else
		{
			_x -= _speed;
			_eyeFrameX = 2;
		}
		break;

	case BS_ATTACK :
		if (_coolDown) changeState(BS_IDLE);

		else
		{
			_bodyFrame = IMAGEMANAGER->findDImage("beholder_attack");

			_invincible = true;
			_attackCount++;

			if (_attackCount > 120)
			{
				_plasma->fire(_x, _y, getAngle(_x, _y, _player->getX(), _player->getY()));
				_coolDown = true;
				_invincible = false;
				_attackCount = 0;
			}
		}
		break;

	case BS_HURT :
		_hurtCount++;
		if (_hurtCount > 30)
		{
			changeState(BS_IDLE);
			_hurtCount = 0;
		}
		break;

	case BS_DYING :
		_individualFrame = 15;
		_dieCount++;
		if (_dieCount > 180)
		{
			changeState(BS_DEAD);
			_dieCount = 0;
		}
		break;

	case BS_DEAD :
		_death = true;
		break;
	}

	if (_coolDown) _coolDownCount++;
	if (_coolDownCount > 180)
	{
		_coolDown = false;
		_coolDownCount = 0;
	}
}

void Boss_beholder::render()
{
	if (_state == BS_ATTACK || _state == BS_HURT || _state == BS_DEAD)
		_bodyFrame->render(_rc.left, _rc.top + _tuningDead);
	else
	_bodyFrame->frameRender(_rc.left, _rc.top, _frameX, 0);
	if (_eyeFrame != nullptr)
	{
		if (_state == BS_IDLE || _state == BS_MOVE)
			_eyeFrame->frameRender(_x - 40, _y - 5, _eyeFrameX, 0);
		else if (_state == BS_ATTACK)
			_eyeFrame->frameRender(_x - 28, _y, _eyeFrameX, 0);
	}

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_detection);
		DTDMANAGER->Rectangle(_detection2);
	}
	_plasma->render();
	controlFrame();
}

void Boss_beholder::controlFrame()
{
	_count++;

	if (_count >= _individualFrame)
	{
		if (_frameX >= _bodyFrame->getMaxFrameX())
		{
			switch (_state)
			{
			case BS_IDLE:
				_frameX = 0;
				break;

			case BS_MOVE :
				_frameX = 0;
				break;

			case BS_DYING:
				_frameX = 0;
				break;
			}
		}
		else
			_frameX++;

		_count = 0;
	}
}

void Boss_beholder::detection()
{
	
	if (_state != BS_HURT && _state != BS_DYING && _state != BS_DEAD)
	{
		RECT rc;
		if (IntersectRect(&rc, &_detection, &_player->getRect()) ||
			IntersectRect(&rc, &_detection2, &_player->getRect()))
		{
			changeState(BS_ATTACK);
		}
		else
			changeState(BS_MOVE);
	}
	
}

void Boss_beholder::changeState(BOSSSTATE state)
{
	_state = state;

	switch (_state)
	{
	case BS_IDLE:
		_bodyFrame = IMAGEMANAGER->findDImage("beholder_idle");
		_eyeFrame = IMAGEMANAGER->findDImage("beholder_eye");
		break;
	case BS_MOVE:
		_bodyFrame = IMAGEMANAGER->findDImage("beholder_idle");
		_eyeFrame = IMAGEMANAGER->findDImage("beholder_eye");
		break;
	case BS_ATTACK:
		_eyeFrameX = 0;
		_bodyFrame = IMAGEMANAGER->findDImage("beholder_attack");
		_eyeFrame = IMAGEMANAGER->findDImage("beholder_eyeX");
		break;
	case BS_HURT:
		_bodyFrame = IMAGEMANAGER->findDImage("beholder_hurt");
		_eyeFrame = nullptr;
		break;
	case BS_DYING:
		_bodyFrame = IMAGEMANAGER->findDImage("beholder_dead");
		_eyeFrame = nullptr;
		break;
	case BS_DEAD :
		_bodyFrame = IMAGEMANAGER->findDImage("beholder_deadFloor");
		_eyeFrame = nullptr;
		break;
	}
}
