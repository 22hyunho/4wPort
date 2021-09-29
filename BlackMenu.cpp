#include "stdafx.h"
#include "BlackMenu.h"

HRESULT BlackMenu::init()
{
	UpMenu::init();

	//배경 이미지
	_back = IMAGEMANAGER->addDImage(
		"blackMenu_back", L"img/fade_B.png", UPMENU_WIDTH, UPMENU_HEIGHT);

	return S_OK;
}

void BlackMenu::release()
{
}

void BlackMenu::update()
{
}

void BlackMenu::render()
{
	UpMenu::render();
}
