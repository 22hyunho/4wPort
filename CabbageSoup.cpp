#include "stdafx.h"
#include "CabbageSoup.h"
#include "Player.h"

HRESULT CabbageSoup::init(Player * player)
{
	player->setBaseAts(30);
	player->changeAtkSpd(10);
	return S_OK;
}
