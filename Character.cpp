#include "stdafx.h"
#include "Character.h"

HRESULT Character::init()
{
	_z = 1;
	_count = 0;
	_tuningX = _tuningY = 0;
	_tuningFrame = 5;
	_direct = 1;

	_invincible = false;
	_hurtCount = 0;
	_alpha = 1.f;

	_dodge = false;
	return S_OK;
}

void Character::release()
{
}

void Character::update()
{
	_direct = _frameY;
	if (_invincible)
	{
		_invCount++;

		if (_invCount % 20 <= 10)
			_alpha = 0.5f;
		else
			_alpha = 1.f;

		if (_invCount > 120)
		{
			_invincible = false;
			_alpha = 1.f;
			_invCount = 0;
		}
	}

	switch (_state)
	{
	case ST_HURT :
		_hurtCount++;
		if (_hurtCount > 15)
		{
			changeState(ST_IDLE);
			_hurtCount = 0;
		}
		break;

	case ST_DIE :
		_dieCount++;
		if (_dieCount > 150)
		{
			CAMERAMANAGER->setFade(FADEOUT);

			if (CAMERAMANAGER->getAlpha() == 1.0)
			{
				SCENEMANAGER->changeScene("gameOver");
				_dieCount = 0;
			}
		}
		break;
	}
}

void Character::render()
{
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);

	_img->frameRender(_x - TILESIZE / 4 + _tuningX, _y - TILESIZE / 2 + _tuningY, _frameX, _frameY);
	if (!UIMANAGER->getOpen()) controlFrame();

	if (PRINTMANAGER->isDebug())
	{
		WCHAR str[128];
		swprintf_s(str, L"x: %f, y: %f", _x, _y);
		DTDMANAGER->printText(str, _x, _rc.top - 20, 150, 20);
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_interactRc);
	}
}

void Character::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= 0.05 * _tuningFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			switch (_state)
			{
			case ST_IDLE :
				_frameX = 0;
				break;
				
			case ST_RUN :
				_frameX = 0;
				break;

			case ST_SHOOT :
				if (_index == CH_HUNTER)
					changeState(ST_IDLE);
				
				else _frameX = 0;
				break;

			case ST_MOVINGSHOOT :
				_frameX = 0;
				break;

			case ST_DODGE :
				if (_index == CH_HUNTER)
				{
					_dodge = false;
					changeState(ST_IDLE);
				}
				else
					_frameX = 0;
				break;

			case ST_DEPLOY :
				changeState(ST_IDLE);
				break;

			case ST_DIE :
				_frameX = _img->getMaxFrameX();
				break;
			}
		}
		else _frameX++;
		
		_count = 0;
	}
}

void Character::changeState(STATE state)
{
	_state = state;

	switch (_state)
	{
	case ST_IDLE :
		_tuningFrame = 5;
		_frameX = 0;
		_tuningY = 0;
		break;

	case ST_RUN :
		_tuningFrame = 2;
		break;

	case ST_AIMING :
		_frameX = 0;
		break;

	case ST_SHOOT :
		_frameX = 0;
		_tuningFrame = 1;
		break;

	case ST_DODGE :
		_frameX = 0;
		_tuningFrame = 1.2f;
		_dodge = true;
		break;

	case ST_DEPLOY :
		_frameX = 0;
		_tuningFrame = 2.f;
		break;

	case ST_HURT :
		_frameX = 0;
		break;

	case ST_DIE :
		_frameX = 0;
		_tuningFrame = 2.f;
		break;
	}
}
