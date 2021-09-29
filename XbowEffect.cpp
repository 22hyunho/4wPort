#include "stdafx.h"
#include "XbowEffect.h"

HRESULT XbowEffect::init(int frameX, int frameY, float x, float y)
{
	Effect::init(frameX, frameY, x, y);
	_img = IMAGEMANAGER->addFrameDImage("xbow_dashAfter", L"img/player/xbow_dash.png", 36, 60, 1, 2);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_type = EF_NONATTACK;
	return S_OK;
}

void XbowEffect::release()
{
}

void XbowEffect::update()
{
	_offCount++;
	if (_offCount > 10)
	{
		_off = true;
	}
}

void XbowEffect::render()
{
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	controlFrame();

	_img->frameRender(_rc.left, _rc.top, _frameX, _frameY, 0.5f);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}

void XbowEffect::controlFrame()
{
}
