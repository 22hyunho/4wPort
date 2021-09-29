#include "stdafx.h"
#include "NPC_cook.h"

HRESULT NPC_cook::init(float x, float y)
{
	NPC::init(x, y);
	_img = IMAGEMANAGER->addDImage("cook", L"img/npc/npc_cook.png", 24, 45);
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
	_interactRc = RectMakeCenter(_x, _y, TILESIZE + 2, TILESIZE + 4);

	return S_OK;
}

void NPC_cook::release()
{
}

void NPC_cook::update()
{
}

void NPC_cook::render()
{
	NPC::render();
}
