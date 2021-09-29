#include "stdafx.h"
#include "CookedBeans.h"
#include "Player.h"

HRESULT CookedBeans::init(Player * player)
{
	player->setBaseHP(player->getBaseHP() + 2);
	player->setMaxHP(player->getMaxHP() + 2);
	player->setCurrentHP(player->getMaxHP());

	player->setBaseAts(30);
	player->changeAtkSpd(10);
	return S_OK;
}
