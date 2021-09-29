#pragma once
#include "Item.h"
class Meat :
	public Item
{
private :

public :
	Meat() {};
	~Meat() {};

	HRESULT init(float x, float y, float angle, int value);
	void release();
	void update();
	void render();

	void move();
};

