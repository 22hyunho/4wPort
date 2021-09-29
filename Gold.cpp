#include "stdafx.h"
#include "Gold.h"

HRESULT Gold::init(float x, float y, float angle, int value)
{
	_img = IMAGEMANAGER->addFrameDImage("gold", L"img/item/gold.png", 60, 39, 2, 1);
	Item::init(x, y, angle, value);
	_type = TY_GOLD;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	if (_value < 10) _frameX = 0;
	else			 _frameX = 1;
	return S_OK;
}

void Gold::release()
{
}

void Gold::update()
{
	move();
}

void Gold::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, 0);
}

void Gold::move()
{
}
