#include "stdafx.h"
#include "MealBread.h"
#include "Player.h"

HRESULT MealBread::init(Player * player)
{
	player->setBaseHP(player->getBaseHP() + 2);
	player->setMaxHP(player->getMaxHP() + 2);
	player->setCurrentHP(player->getMaxHP());
	return S_OK;
}
