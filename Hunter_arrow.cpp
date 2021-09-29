#include "stdafx.h"
#include "Hunter_arrow.h"

HRESULT Hunter_arrow::init(float x, float y, float angle)
{
	_img = new dImage;
	_img->init(L"img/arrow/hunter_arrowWhite.png", 36, 9);
	_range = WINSIZEX;
	_x = _fireX = x;
	_y = _fireY = y;
	_angle = angle;
	_off = false;
	_speed = 45;
	_rc = RectMakeCenter(_x, _y, 10, 10);
	return S_OK;
}

void Hunter_arrow::release()
{
	_img->release();
	SAFE_DELETE(_img);
}

void Hunter_arrow::update()
{
	Arrow::update();
	move();
} 

void Hunter_arrow::render()
{
	DTDMANAGER->setRotate(TODEGREE(_angle) * -1, _x, _y);
	_img->render(_rc.left - _img->getWidth() + 10, _rc.top - _img->getHeight() + 10);
	DTDMANAGER->resetTransform();

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		WCHAR str[128];
		swprintf_s(str, L"angle : %f", _angle);
		DTDMANAGER->printText(str, _x, _rc.top - 30, 150, 20);
	}
}

void Hunter_arrow::move()
{
	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_x, _y, 10, 10);

	if (getDistance(_x, _y, _fireX, _fireY) >= _range)
		_off = true;
}
