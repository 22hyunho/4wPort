#include "stdafx.h"
#include "Oatmeal.h"
#include "Player.h"

HRESULT Oatmeal::init(Player * player)
{
	player->setBaseDmg(player->getBaseDmg() + 20);
	player->changeDamage(20);
	return S_OK;
}
