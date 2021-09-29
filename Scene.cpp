#include "stdafx.h"
#include "Scene.h"
#include "Player.h"

Player* Scene::_player = NULL;

HRESULT Scene::init(Player * player)
{
	_player = player;
	_keyE = IMAGEMANAGER->addDImage("keyE", L"img/ui/keyboard_E1.png", 48, 47);
	IMAGEMANAGER->addDImage("bossHP_top", L"img/boss/hpBar_Top.png", 745, 70);
	IMAGEMANAGER->addDImage("bossHP_bot", L"img/boss/hpBar_bottom.png", 695, 45);
	return S_OK;
}