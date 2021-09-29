#include "stdafx.h"
#include "Egg.h"
#include "Player.h"

HRESULT Egg::init(Player * player)
{
	player->setChance(true);
	return S_OK;
}
