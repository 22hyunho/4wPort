#pragma once
#include "Enemy.h"
class Bat :
	public Enemy
{
private :

public :
	Bat() {};
	~Bat() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

