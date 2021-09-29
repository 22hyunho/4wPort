#include "stdafx.h"
#include "TrapMenu.h"
#include "Player.h"

HRESULT TrapMenu::init(Player* player)
{
	Menu::init(player);

	IMAGEMANAGER->addDImage("selected", L"img/ui/trap_selected.png", 134, 39);
	IMAGEMANAGER->addDImage("bearInfo", L"img/trap/bearTrap_info.png", 78, 57);
	IMAGEMANAGER->addDImage("slowInfo", L"img/trap/slowTrap_info.png", 80, 60);
	_rune = IMAGEMANAGER->addDImage("rune_ui", L"img/ui/rune_ui.png", 54, 65);
	_back = IMAGEMANAGER->addDImage("background", L"img/ui/black.png", WINSIZEX, WINSIZEY);
	_border[0] = IMAGEMANAGER->addDImage("border1", L"img/ui/black.png", 550, 600);
	_border[1] = IMAGEMANAGER->addDImage("border2", L"img/ui/black.png", 400, 600);
	_select[0] = IMAGEMANAGER->addDImage("bearSelect", L"img/ui/trap_select.png", 110, 50);
	_select[1] = IMAGEMANAGER->addDImage("slowSelect", L"img/ui/trap_select.png", 110, 50);
	_trapBack[0] = IMAGEMANAGER->addFrameDImage("trapBack1", L"img/ui/trap_background.png", 268, 125, 2, 1);
	_trapBack[1] = IMAGEMANAGER->addFrameDImage("trapBack2", L"img/ui/trap_background.png", 268, 125, 2, 1);
	_level[0] = IMAGEMANAGER->addFrameDImage("trapLevel1", L"img/ui/trap_level.png", 676, 127, 4, 1);
	_level[1] = IMAGEMANAGER->addFrameDImage("trapLevel2", L"img/ui/trap_level.png", 676, 127, 4, 1);

	_screen = CAMERAMANAGER->getScreen();
	_info[0] = RectMake(_screen.left + 20, _screen.top + 160, 550, 120);
	_info[1] = RectMake(_screen.left + 20, _screen.top + 300, 550, 120);
	_choice[0] = RectMake(_screen.left + 40, _screen.top + 200, 110, 50);
	_choice[1] = RectMake(_screen.left + 40, _screen.top + 340, 110, 50);
	_levelUp[0] = RectMake(_screen.left + 355, _screen.top + 159, 169, 120);
	_levelUp[1] = RectMake(_screen.left + 355, _screen.top + 299, 169, 120);

	_currentTrap = _player->getTrap();
	return S_OK;
}

void TrapMenu::release()
{
}

void TrapMenu::update()
{
	for (int i = 0; i < 2; i++)
	{
		if (PtInRect(&_choice[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				switch (i)
				{
				case 0:
					_currentTrap = TRAP_BEAR;
					_player->setTrap(TRAP_BEAR);
					break;

				case 1:
					_currentTrap = TRAP_SLOW;
					_player->setTrap(TRAP_SLOW);
					break;
				}
		}
		if (PtInRect(&_levelUp[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			switch (i)
			{
			case 0:
				if (_bearLevel == 1 && _player->getRune() >= 10)
				{
					_player->changeRune(-10);
					_player->plusBearLevel();
				}
				else if (_bearLevel == 2 && _player->getRune() >= 15)
				{
					_player->changeRune(-15);
					_player->plusBearLevel();
				}
				break;

			case 1:
				if (_slowLevel == 1 && _player->getRune() >= 15)
				{
					_player->changeRune(-15);
					_player->plusSlowLevel();
				}
				break;
			}
		}
	}

	switch (_currentTrap)
	{
	case TRAP_BEAR :
		_select[0] = IMAGEMANAGER->findDImage("selected");
		_select[1] = IMAGEMANAGER->findDImage("slowSelect");
		break;

	case TRAP_SLOW :
		_select[0] = IMAGEMANAGER->findDImage("bearSelect");
		_select[1] = IMAGEMANAGER->findDImage("selected");
		break;
	}

	_bearLevel = _player->getBearLevel();
	_slowLevel = _player->getSlowLevel();
}

void TrapMenu::render()
{
	Menu::render();
	_border[0]->render(_screen.left + 20, _screen.top + 100, 0.7f);
	_border[1]->render(_screen.left + 580, _screen.top + 100, 0.7f);

	if (_select[0] == IMAGEMANAGER->findDImage("selected"))
		_select[0]->render(_screen.left + 30, _screen.top + 200);
	else _select[0]->render(_screen.left + 40, _screen.top + 200);
	_trapBack[0]->frameRender(_screen.left + 180, _screen.top + 160, 0, 0);
	IMAGEMANAGER->findDImage("bearInfo")->render(_screen.left + 210, _screen.top + 195);
	_level[0]->frameRender(_screen.left + 355, _screen.top + 159, _bearLevel, 0);

	_trapBack[1]->frameRender(_screen.left + 180, _screen.top + 300, 0, 0);
	IMAGEMANAGER->findDImage("slowInfo")->render(_screen.left + 208, _screen.top + 335);
	_level[1]->frameRender(_screen.left + 355, _screen.top + 299, _slowLevel, 0);
	if (_select[1] == IMAGEMANAGER->findDImage("selected"))
		_select[1]->render(_screen.left + 30, _screen.top + 340);
	else _select[1]->render(_screen.left + 40, _screen.top + 340);

	
	for (int i = 0; i < 2; i++)
	{
		if (PRINTMANAGER->isDebug())
		{
			DTDMANAGER->Rectangle(_info[i]);
			DTDMANAGER->Rectangle(_choice[i]);
			DTDMANAGER->Rectangle(_levelUp[i]);
		}

		if (PtInRect(&_info[i], _ptMouse))
		{
			switch (i)
			{
			case 0:
				bearTrapInfo();
				break;

			case 1:
				slowTrapInfo();
				break;
			}
		}
	}
	
}

void TrapMenu::bearTrapInfo()
{
	DTDMANAGER->printText(L"베어 트랩", _screen.left + 792, _screen.top + 180, 250, 50, 50);
	DTDMANAGER->printText(L"Lv. 1 \n 적이 밟게되면 피해를 입습니다.", _screen.left + 850, _screen.top + 350, 500, 200, 25);
	DTDMANAGER->printText(L"LV. 2 \n 적에게 입히는 피해가 \n 증가합니다.", _screen.left + 850, _screen.top + 450, 500, 200, 25);
	DTDMANAGER->printText(L"LV. 3 \n 총 두개의 트랩을 설치할 수 \n 있습니다.", _screen.left + 850, _screen.top + 550, 500, 200, 25);

	if (_bearLevel == 1)
	{
		DTDMANAGER->printText(L"강     화 :   10", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
	else if (_bearLevel == 2)
	{
		DTDMANAGER->printText(L"강     화 :   15", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void TrapMenu::slowTrapInfo()
{
	DTDMANAGER->printText(L"끈적이 거미줄", _screen.left + 792, _screen.top + 180, 350, 50, 50);
	DTDMANAGER->printText(L"Lv. 1 \n 적이 밟게되면 둔화 상태이상 \n 효과를 받습니다.", _screen.left + 850, _screen.top + 350, 500, 200, 25);
	DTDMANAGER->printText(L"LV. 2 \n 둔화 상태이상 효과와 중독 \n 상태이상 효과를 받습니다.", _screen.left + 850, _screen.top + 450, 500, 200, 25);

	if (_slowLevel == 1)
	{
		DTDMANAGER->printText(L"강     화 :   15", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}
