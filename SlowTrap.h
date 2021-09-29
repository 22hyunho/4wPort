#pragma once
#include "Trap.h"
class SlowTrap :
	public Trap
{
private :

public :
	SlowTrap() {};
	~SlowTrap() {};

	HRESULT init(float x, float y, POINT point, int level);
	void release();
	void update();
	void render();
	void controlFrame();

	void move();
};

