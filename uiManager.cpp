#include "stdafx.h"
#include "uiManager.h"
#include "TrapMenu.h"
#include "FoodMenu.h"

HRESULT uiManager::init(Player* player)
{
	_currentMenu = NULL;
	addMenu("trapMenu", new TrapMenu);
	addMenu("foodMenu", new FoodMenu);

	_openWindow = false;
	_player = player;
	return S_OK;
}

void uiManager::release()
{
	_miMenu = _mMenu.begin();

	for (; _miMenu != _mMenu.end();)
	{
		if (_miMenu->second != NULL)
		{
			if (_miMenu->second == _currentMenu) _miMenu->second->release();
			SAFE_DELETE(_miMenu->second);
			_miMenu = _mMenu.erase(_miMenu);
		}
		else ++_miMenu;
	}

	_mMenu.clear();
}

void uiManager::update()
{
	if (_currentMenu) _currentMenu->update();
}

void uiManager::render()
{
	if (_currentMenu) _currentMenu->render();
}

Menu * uiManager::addMenu(string menuName, Menu * menu)
{
	if (!menu) return nullptr;

	_mMenu.insert(make_pair(menuName, menu));

	return menu;
}

HRESULT uiManager::changeMenu(string menuName)
{
	if (menuName == "NULL") {
		_currentMenu->release();
		_currentMenu = NULL;
	}

	_miMenu = _mMenu.find(menuName);

	if (_miMenu == _mMenu.end()) return E_FAIL;

	if (_miMenu->second == _currentMenu) return S_OK;

	if (SUCCEEDED(_miMenu->second->init(_player)))
	{
		//����(�ִ�) ���� ������ �Լ��� �������ְ�
		if (_currentMenu) _currentMenu->release();

		//�ٲٷ��� ���� ��������� ü����
		_currentMenu = _miMenu->second;

		//CAMERAMANAGER->setFade(FADEIN);

		return S_OK;
	}

	return E_FAIL;
}
