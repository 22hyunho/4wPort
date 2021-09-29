#include "stdafx.h"
#include "NPC_taylor.h"

HRESULT NPC_taylor::init(float x, float y)
{
	NPC::init(x, y);
	_img = IMAGEMANAGER->addDImage("taylor", L"img/npc/npc_taylor.png", 24, 48);
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
	_interactRc = RectMakeCenter(_x, _y, TILESIZE + 2, TILESIZE + 4);

	return S_OK;
}

void NPC_taylor::release()
{
}

void NPC_taylor::update()
{
}

void NPC_taylor::render()
{
	NPC::render();
}
