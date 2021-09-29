#include "stdafx.h"
#include "BearTrap.h"

HRESULT BearTrap::init(float x, float y, POINT point, int level)
{
	_img = new dImage;
	_img->init(L"img/trap/bearTrap.png", 180, 105, 4, 2);
	Trap::init(x, y, point, level);
	_damage = 40;
	_type = BEARTRAP;
	return S_OK;
}

void BearTrap::release()
{
	_img->release();
	SAFE_DELETE(_img);
}

void BearTrap::update()
{
	Trap::update();
	if (_range > 140) _range = 140;
	if (getDistance(_fireX, _fireY, _x, _y) < _range) move();
	else											  _deploy = true;

	if (_unfold)
	{
		_offCount++;
		if (_offCount >= 80)
		{
			_off = true;
		}
	}

	if (_level == 1) _damage = 40;
	else if (_level == 2) _damage = 70;
}

void BearTrap::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY);

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		WCHAR str[128];
		swprintf_s(str, L"angle : %f", _angle);
		DTDMANAGER->printText(str, _x, _rc.top - 30, 150, 20);
	}
	controlFrame();
}

void BearTrap::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.1)
	{
		if (_deploy && !_unfold)	_frameX++;
		else if (_unfold)			_frameX--;

		if (_frameX > _img->getMaxFrameX())
			_frameX = _img->getMaxFrameX();
		else if (_frameX < 0)
			_frameX = 0;

		_count = 0;
	}
}

void BearTrap::move()
{
	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}
