#include "stdafx.h"
#include "NPC_skill.h"

HRESULT NPC_skill::init(float x, float y)
{
	NPC::init(x, y);
	_img = IMAGEMANAGER->addDImage("skill", L"img/npc/npc_skill.png", 45, 27);
	_rc = RectMakeCenter(_x, _y, TILESIZE, TILESIZE / 2);
	_interactRc = RectMakeCenter(_x, _y, TILESIZE + 2, TILESIZE + 4);

	return S_OK;
}

void NPC_skill::release()
{
}

void NPC_skill::update()
{
}

void NPC_skill::render()
{
	NPC::render();
}
