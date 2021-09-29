#include "stdafx.h"
#include "Meat.h"

HRESULT Meat::init(float x, float y, float angle, int value)
{
	_img = IMAGEMANAGER->addDImage("meat", L"img/item/meat.png", 33, 33);
	_x = x;
	_y = y;
	_angle = angle;

	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_type = TY_MEAT;
	_value = 2;

	return S_OK;
}

void Meat::release()
{
}

void Meat::update()
{
	move();
}

void Meat::render()
{
	_img->render(_rc.left, _rc.top);
}

void Meat::move()
{
	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
}
