#include "stdafx.h"
#include "Effect.h"

HRESULT Effect::init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_frameX = 0;
	_frameY = 0;
	_count = 0;
	_offCount = 0;
	return S_OK;
}

HRESULT Effect::init(int frameX, int frameY, float x, float y)
{
	_x = x;
	_y = y;
	_frameX = frameX;
	_frameY = frameY;
	_count = 0;
	_offCount = 0;
	return S_OK;
}

HRESULT Effect::init(float x, float y, float angle)
{
	_x = _fireX = x;
	_y = _fireY = y;
	_angle = angle;
	_frameX = 0;
	_frameY = 0;
	_count = 0;
	_offCount = 0;
	return S_OK;
}

HRESULT Effect::init(float x, float y, bool reverse)
{
	_x = x;
	_y = y;
	_reverse = reverse;
	_count = 0;
	_offCount = 0;
	return S_OK;
}
