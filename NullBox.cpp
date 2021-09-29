#include "stdafx.h"
#include "NullBox.h"

HRESULT NullBox::init(float x, float y, int width, int height)
{
	Effect::init(x, y, width, height);

	_width = width;
	_height = height;

	_type = EF_ATTACK;

	_damage = 2;
	return S_OK;
}

void NullBox::release()
{
}

void NullBox::update()
{
	_offCount++;
	if (_offCount > 30)
	{
		_off = true;
	}

	if (PRINTMANAGER->isDebug())
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void NullBox::render()
{
	//if (PRINTMANAGER->isDebug())
	DTDMANAGER->Rectangle(_rc);
}
