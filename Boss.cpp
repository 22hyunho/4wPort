#include "stdafx.h"
#include "Boss.h"

HRESULT Boss::init(float x, float y, Player* player)
{
	_player = player;
	_x = x;
	_y = y;
	_z = 1;
	_count = 0;
	_frameX = _frameY = 0;

	_state = BS_IDLE;

	_individualFrame = 0;
	_invincible = false;
	_death = false;
	_start = false;
	return S_OK;
}

void Boss::changeHP(int damage)
{
	_currentHP -= damage;
}
