#include "stdafx.h"
#include "Item.h"

HRESULT Item::init(float x, float y, float angle, int value)
{
	_x = x;
	_y = y;
	_angle = angle;
	_value = value;
	_speed = 5;
	return S_OK;
}
