#include "stdafx.h"
#include "Slash1.h"

HRESULT Slash1::init(float x, float y, int width, int height)
{
	Effect::init(x, y, width, height);
	_img = IMAGEMANAGER->addFrameDImage("slash_red", L"img/effect/slash_red.png", 88, 76, 2, 2);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_type = EF_ATTACK;

	_damage = 3;
	return S_OK;
}

void Slash1::release()
{
}

void Slash1::update()
{
}

void Slash1::render()
{
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	controlFrame();

	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}

void Slash1::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count > 0.2f)
	{
		if (_frameX >= _img->getMaxFrameX())
			_off = true;

		else
			_frameX++;

		_count = 0;
	}
}
