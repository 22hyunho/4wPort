#include "stdafx.h"
#include "RabbitStew.h"
#include "Player.h"

HRESULT RabbitStew::init(Player * player)
{
	player->setBaseDmg(player->getBaseDmg() + 20);
	player->changeDamage(20);

	player->setChance(true);
	return S_OK;
}
