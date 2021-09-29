#pragma once
#include "Item.h"
class Rune :
	public Item
{
private :

public :
	Rune() {};
	~Rune() {};

	HRESULT init(float x, float y, float angle, int value);
	void release();
	void update();
	void render();

	void move();
};

