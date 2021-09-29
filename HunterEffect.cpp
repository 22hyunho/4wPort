#include "stdafx.h"
#include "HunterEffect.h"

HRESULT HunterEffect::init(int frameX, int frameY, float x, float y)
{
	Effect::init(frameX, frameY, x, y);
	_img = IMAGEMANAGER->addFrameDImage("hunter_dashAfter", L"img/player/hunter_roll.png", 459, 108, 9, 2);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_type = EF_NONATTACK;
	return S_OK;
}

void HunterEffect::release()
{
}

void HunterEffect::update()
{
	_offCount++;
	if (_offCount > 20)
	{
		_off = true;
	}
}

void HunterEffect::render()
{
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	controlFrame();

	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY, 0.5f);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}

void HunterEffect::controlFrame()
{
}
