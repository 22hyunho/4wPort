#include "stdafx.h"
#include "Trap.h"

HRESULT Trap::init(float x, float y, POINT point, int level)
{
	_x = _fireX = x;
	_y = _fireY = y;
	_angle = getAngle(x, y, point.x, point.y);
	_range = getDistance(_fireX, _fireY, point.x, point.y);
	_frameX = _frameY = 0;
	_offCount = 0;
	_level = level;
	_off = false;
	_deploy = false;
	_unfold = false;
	_speed = 3;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	return S_OK;
}

void Trap::update()
{
	COLLISIONMANAGER->collisionTrap(this);
}
