#include "stdafx.h"
#include "bossEffect2_2.h"

HRESULT bossEffect2_2::init(float x, float y, bool reverse)
{
	Effect::init(x, y, reverse);
	_img = IMAGEMANAGER->addFrameDImage("spellEffect", L"img/effect/bossEffect2_2.png", 516, 155, 8, 1);
	_rc = RectMakeCenter(_x, _y, TILESIZE, TILESIZE);

	_type = EF_ATTACK;

	_damage = 4;
	return S_OK;
}

void bossEffect2_2::release()
{
}

void bossEffect2_2::update()
{
}

void bossEffect2_2::render()
{
	_img->frameRender(_rc.left - 8, _rc.top - 104, _frameX, 0);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);

	controlFrame();
}

void bossEffect2_2::controlFrame()
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
