#pragma once
#include "singletonBase.h"
#include "Menu.h"

class Player;

class uiManager : public singletonBase<uiManager>
{
private :
	typedef map<string, Menu*>				menuList;
	typedef map<string, Menu*>::iterator	menuIter;

private :
	menuList _mMenu;
	menuIter _miMenu;

	Menu* _currentMenu;

	Player* _player;
	bool _openWindow;

public :
	uiManager() {};
	~uiManager() {};

	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	Menu* addMenu(string menuName, Menu* menu);
	HRESULT changeMenu(string menuName);

	//=====================접근자&설정자=====================

	bool getOpen() { return _openWindow; }
	void setOpen(bool open) { _openWindow = open; }
};

