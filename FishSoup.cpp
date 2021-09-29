#include "stdafx.h"
#include "FishSoup.h"
#include "Player.h"

HRESULT FishSoup::init(Player * player)
{
	player->setBaseDmg(player->getBaseDmg() + 20);
	player->changeDamage(20);

	player->setBaseAts(30);
	player->changeAtkSpd(10);

	player->setChance(true);
	return S_OK;
}
