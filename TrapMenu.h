#pragma once
#include "Menu.h"

class TrapMenu :
	public Menu
{
private :
	dImage* _select[3];
	dImage* _trapBack[3];
	dImage* _level[3];
	dImage* _rune;

	RECT _info[3];
	RECT _choice[3];
	RECT _levelUp[3];

	int _currentTrap;

	int _bearLevel;
	int _slowLevel;
public :
	TrapMenu() {};
	~TrapMenu() {};

	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void bearTrapInfo();
	void slowTrapInfo();
};

