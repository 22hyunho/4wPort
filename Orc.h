#pragma once
#include "Enemy.h"
class Orc :
	public Enemy
{
private:

public:
	Orc() {};
	~Orc() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

