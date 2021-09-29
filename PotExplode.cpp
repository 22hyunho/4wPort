#include "stdafx.h"
#include "PotExplode.h"

HRESULT PotExplode::init(float x, float y, int width, int height)
{
	Effect::init(x, y, width, height);
	_img = IMAGEMANAGER->addFrameDImage("potExplode", L"img/enemy/plant/plantPot_explode.png", 648, 207, 12, 1);
	_rc = RectMakeCenter(_x, _y, TILESIZE * 3, TILESIZE * 3);

	_type = EF_ATTACK;

	_damage = 3;

	return S_OK;
}

void PotExplode::release()
{
}

void PotExplode::update()
{
}

void PotExplode::render()
{
	_img->frameRender(_rc.left + 47, _rc.top - 110, _frameX, 0);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);

	controlFrame();
}

void PotExplode::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.1)
	{
		if (_frameX >= _img->getMaxFrameX())
			_off = true;

		else
			_frameX++;

		_count = 0;
	}
}
