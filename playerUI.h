#pragma once
#include "singletonBase.h"

class Player;

class playerUI : public singletonBase<playerUI>
{
private :
	dImage* _heart[10];
	dImage* _half[10];
	dImage* _armor;
	dImage* _stone[2];
	dImage* _gold;
	dImage* _rune;
	dImage* _trap;
	dImage* _keyQ;

	Player* _player;

	float _alpha;

public :
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void setTrapImage(dImage* image) { _trap = image; }
};

