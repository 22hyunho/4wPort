#include "stdafx.h"
#include "Pattern_default.h"
#include "Player.h"
#include "Enemy.h"

HRESULT Pattern_default::init(Player * player)
{
	Pattern::init(player);
	_enemy->changeState(ES_IDLE);
	return S_OK;
}

HRESULT Pattern_default::init(Enemy * enemy)
{
	Pattern::init(enemy);
	return S_OK;
}

void Pattern_default::release()
{
}

void Pattern_default::update()
{
}

void Pattern_default::render()
{
}
