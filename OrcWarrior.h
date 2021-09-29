#pragma once
#include "Enemy.h"
class OrcWarrior :
	public Enemy
{
private:

public:
	OrcWarrior() {};
	~OrcWarrior() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

