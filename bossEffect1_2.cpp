#include "stdafx.h"
#include "bossEffect1_2.h"

HRESULT bossEffect1_2::init(float x, float y, int width, int height)
{
	Effect::init(x, y, width, height);
	_img = IMAGEMANAGER->addFrameDImage("explodeEffect", L"img/effect/bossEffect1_2.png", 3060, 268, 9, 1);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_type = EF_ATTACK;

	_damage = 4;
	return S_OK;
}

void bossEffect1_2::release()
{
}

void bossEffect1_2::update()
{
}

void bossEffect1_2::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, 0);

	if (PRINTMANAGER->isDebug())
	DTDMANAGER->Rectangle(_rc);

	controlFrame();
}

void bossEffect1_2::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.1f)
	{
		if (_frameX >= _img->getMaxFrameX())
			_off = true;

		else
			_frameX++;

		_count = 0;
	}
}
