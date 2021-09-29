#include "stdafx.h"
#include "Rune.h"

HRESULT Rune::init(float x, float y, float angle, int value)
{
	_img = IMAGEMANAGER->addDImage("rune", L"img/item/rune.png", 30, 36);
	Item::init(x, y, angle, value);
	_type = TY_RUNE;

	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	return S_OK;
}

void Rune::release()
{
}

void Rune::update()
{
	move();
}

void Rune::render()
{
	_img->render(_rc.left, _rc.top);
	//DTDMANAGER->Rectangle(_rc);
}

void Rune::move()
{
}
