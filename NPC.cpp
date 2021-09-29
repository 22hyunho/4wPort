#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init(float x, float y)
{
	_x = x;
	_y = y;
	return S_OK;
}

void NPC::release()
{
}

void NPC::update()
{
}

void NPC::render()
{
	_img->render(_rc.left, _rc.top);
	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_interactRc);
	}
}
