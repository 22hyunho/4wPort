#pragma once
#include "Enemy.h"
class Spider :
	public Enemy
{
private :

public :
	Spider() {};
	~Spider() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

