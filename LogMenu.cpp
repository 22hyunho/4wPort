#include "stdafx.h"
#include "LogMenu.h"

HRESULT LogMenu::init()
{
	//배경 이미지
	_back = IMAGEMANAGER->addDImage(
		"logMenu_back", L"img/UI/logMenu/back.png", DOWNMENU_WIDTH, DOWNMENU_HEIGHT);
	_border = IMAGEMANAGER->addDImage(
		"logMenu_border", L"img/UI/logMenu/border.png", DOWNMENU_WIDTH, DOWNMENU_HEIGHT);

	_tuningX = 0;
	_tuningY = 0;

	_logList = DIALOGMANAGER->getBattleLog();

	_hidden = true;

	return S_OK;
}

void LogMenu::release()
{
}

void LogMenu::update()
{
	
}

void LogMenu::render()
{
	if (_hidden) return;

	DownMenu::render();
	//타이머
	if (TIMEMANAGER->clock() >= 4) {
		_hidden = true;
		TIMEMANAGER->endTimer();
	}


	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

	logIter iter;
	int count = 0;

	if (_logList->size() > 6)
		iter = _logList->end() - 6;
	else
		iter = _logList->begin();

	for (; iter != _logList->end(); ++iter) {

		DTDMANAGER->printText(iter->c_str(), 
			screen.left + DOWNMENU_WIDTH / 2, screen.bottom - 144 + count * 20,
			480, 20, 20);
		count++;
	}
}