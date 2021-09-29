#include "stdafx.h"
#include "NPC_blacksmith.h"

HRESULT NPC_blacksmith::init(float x, float y)
{
	NPC::init(x, y);
	_img = IMAGEMANAGER->addDImage("blacksmith", L"img/npc/npc_blacksmith.png", 21, 45);
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
	_interactRc = RectMakeCenter(_x, _y, TILESIZE + 2, TILESIZE + 4);
	return S_OK;
}

void NPC_blacksmith::release()
{
}

void NPC_blacksmith::update()
{
}

void NPC_blacksmith::render()
{
	NPC::render();
}
