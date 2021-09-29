#include "stdafx.h"
#include "MainMenu.h"

HRESULT MainMenu::init()
{
	//배경 이미지
	_back = IMAGEMANAGER->addDImage(
		"mainMenu_back", L"img/UI/mainMenu/back.png", MAINMENU_WIDTH, MAINMENU_HEIGHT);
	_border = IMAGEMANAGER->addDImage(
		"mainMenu_border", L"img/UI/mainMenu/border.png", MAINMENU_WIDTH, MAINMENU_HEIGHT);

	//선택 화살표
	_arrow = IMAGEMANAGER->addDImage("selectTri", L"img/UI/mainMenu/tri.png", 10, 22);

	_tuningX = 2 * TILEWIDTH / 3;
	_tuningY = TILEHEIGHT / 2;

	_index = 0;

	_rc = CAMERAMANAGER->getScreen();

	return S_OK;
}

void MainMenu::release()
{
}

void MainMenu::update()
{
	if (KEYMANAGER->isOnceKeyDown(KEY_DOWN)) {
		SOUNDMANAGER->play("Index");
		_index = (_index + 1) % END_MAINMENU_OPTION;
	}
	else if (KEYMANAGER->isOnceKeyDown(KEY_UP)) {
		SOUNDMANAGER->play("Index");
		_index = (_index - 1 + END_MAINMENU_OPTION) % END_MAINMENU_OPTION;
	}

	if (KEYMANAGER->isOnceKeyDown(KEY_A)) {
		SOUNDMANAGER->play("Select");
		if (_index == MAINMENU_OPTION_SKILL)
			UIMANAGER->changeDownMenu("skillMenu");
		else if (_index == MAINMENU_OPTION_INVENTORY)
			UIMANAGER->changeDownMenu("invenMenu");
	}

	if (KEYMANAGER->isOnceKeyDown(KEY_B)) {
		SOUNDMANAGER->play("Cancel");
		UIMANAGER->changeDownMenu("logMenu");
		UIMANAGER->setOpen(false);
	}


	_count++;
	if (_count > 20) {
		_opacity = !_opacity;
		_count = 0;
	}
}

void MainMenu::render()
{
	DownMenu::render();
	
	//LEFT(메뉴 목록)
	printTextLeft();

	//RIGHT(던전 이름)
	printTextRight();

	//DOWN(현재 stat)
	printTextDown();
}

void MainMenu::printTextLeft()
{
	D2D1_RECT_F dest = dRectMake(_rc.left + _tuningX + TILEWIDTH, _rc.top + _tuningY + TILEHEIGHT / 2,
		TILEWIDTH * 2, TILEHEIGHT);

	//화살표
	_arrow->render(dest.left - 20, dest.top + _index * TILEHEIGHT, _opacity);

	DTDMANAGER->printText(L"기술", dest, 25);

	dest.top += TILEHEIGHT;
	dest.bottom += TILEHEIGHT;
	DTDMANAGER->printText(L"도구", dest, 25);

}

void MainMenu::printTextRight()
{
	
	D2D1_RECT_F dest2 = dRectMakeCenter(_rc.right - 225, _rc.top + 125, 200, 200);
	
	DTDMANAGER->printText(TILEMANAGER->getDungeonName().c_str(), dest2, 25, true);
}

void MainMenu::printTextDown()
{
	D2D1_RECT_F downDest = dRectMake(_rc.left + _tuningX + TILEWIDTH + TILEWIDTH / 2, _rc.top + 5 + _tuningY + 10 + TILEHEIGHT * 8, TILEWIDTH * 10, TILEHEIGHT);
	D2D1_RECT_F downDest2 = dRectMake(_rc.left + _tuningX + TILEWIDTH * 7, _rc.top + 5 + _tuningY + 10 + TILEHEIGHT * 8, TILEWIDTH * 10, TILEHEIGHT);

	Player* player = (*TURNMANAGER->getAllPlayer())[0];
	DTDMANAGER->printText(player->getPokemon()->getName().c_str(), downDest, 25);	   

	WCHAR text[128];
	swprintf_s(text, L"배: %d / 100", player->getStarve());
	DTDMANAGER->printText(text, downDest2, 25);
	downDest2.top += 30;
	downDest2.bottom += 30;
	DTDMANAGER->printText(L"돈: ", downDest2, 25);
	downDest2.top += 30;
	downDest2.bottom += 30;
	DTDMANAGER->printText(L"날씨: ", downDest2, 25);
	downDest2.top += 30;
	downDest2.bottom += 30;
	DTDMANAGER->printText(L"시간: ", downDest2, 25);
}
