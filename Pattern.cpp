#include "stdafx.h"
#include "Pattern.h"

HRESULT Pattern::init(Player * player)
{
	_player = player;
	return S_OK;
}

HRESULT Pattern::init(Enemy * enemy)
{
	_enemy = enemy;
	return S_OK;
}
