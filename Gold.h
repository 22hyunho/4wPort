#pragma once
#include "Item.h"
class Gold :
	public Item
{
private :
	int _frameX;

public :
	Gold() {};
	~Gold() {};

	HRESULT init(float x, float y, float angle, int value);
	void release();
	void update();
	void render();

	void move();
};

