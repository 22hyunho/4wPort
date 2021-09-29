#include "stdafx.h"
#include "SlowTrap.h"

HRESULT SlowTrap::init(float x, float y, POINT point, int level)
{
	_img = IMAGEMANAGER->addFrameDImage("slowTrap", L"img/trap/slowTrap.png", 413, 80, 5, 1);
	Trap::init(x, y, point, level);

	_type = SLOWTRAP;
	_level = 0;
	_damage = 0;
	_slow = 3;
	return S_OK;
}

void SlowTrap::release()
{
	_img->release();
	SAFE_DELETE(_img);
}

void SlowTrap::update()
{
	Trap::update();
	if (_range > 140) _range = 140;
	if (getDistance(_fireX, _fireY, _x, _y) < _range) move();
	else											  _deploy = true;
}

void SlowTrap::render()
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

void SlowTrap::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.1)
	{
		if (_deploy) _frameX++;
		else		 _frameX--;

		if (_frameX > _img->getMaxFrameX())
			_frameX = _img->getMaxFrameX();
		else if (_frameX < 0)
			_frameX = 0;

		_count = 0;
	}
}

void SlowTrap::move()
{
	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}
