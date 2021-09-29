#include "stdafx.h"
#include "HoneyBoar.h"
#include "Player.h"

HRESULT HoneyBoar::init(Player * player)
{
	player->setBaseHP(player->getBaseHP() + 2);
	player->setMaxHP(player->getMaxHP() + 2);
	player->setCurrentHP(player->getMaxHP());

	player->setBaseAts(30);
	player->changeAtkSpd(10);

	player->setChance(true);
	return S_OK;
}
