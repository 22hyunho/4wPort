#include "stdafx.h"
#include "bossEffect2_1.h"

HRESULT bossEffect2_1::init(float x, float y, bool reverse)
{
	Effect::init(x, y, reverse);
	_img = IMAGEMANAGER->addFrameDImage("lockon", L"img/effect/bossEffect2_1.png", 205, 21, 5, 1);
	_rc = RectMakeCenter(_x, _y, TILESIZE, TILESIZE);

	_type = EF_NONATTACK;

	return S_OK;
}

void bossEffect2_1::release()
{
}

void bossEffect2_1::update()
{
}

void bossEffect2_1::render()
{
	_img->frameRender(_rc.left + 4, _rc.top + 27, _frameX, 0);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);

	controlFrame();
}

void bossEffect2_1::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.13f)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			_off = true;
		}

		else
			_frameX++;

		_count = 0;
	}
}
