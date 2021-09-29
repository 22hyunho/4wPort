#pragma once
#include "Trap.h"
class BearTrap :
	public Trap
{
private :

public :
	BearTrap() {};
	~BearTrap() {};

	HRESULT init(float x, float y, POINT point, int level);
	void release();
	void update();
	void render();
	void controlFrame();

	void move();
};

