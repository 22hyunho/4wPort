#include "stdafx.h"
#include "Menu.h"

HRESULT Menu::init(Player * player)
{
	_player = player;

	return S_OK;
}

void Menu::render()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_back->render(screen.left, screen.top, 0.5f);
}
