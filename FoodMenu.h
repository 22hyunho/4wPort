#pragma once
#include "Menu.h"
#include "Food.h"
class FoodMenu :
	public Menu
{
	dImage* _border[2];
	dImage* _foodBack[8];
	dImage* _level[3];
	dImage* _rune;
	dImage* _selected;

	RECT _choice[9];

	Food* _food;

	int _currentFood;
public:
	FoodMenu() {};
	~FoodMenu() {};

	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void eggInfo();
	void breadInfo();
	void oatmealInfo();
	void cabbagesoupInfo();
	void rabbitstewInfo();
	void cookedbeansInfo();
	void fishsoupInfo();
	void honeyboarInfo();
};

