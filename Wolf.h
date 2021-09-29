#pragma once
#include "Enemy.h"
class Wolf :
	public Enemy
{
private :

public :
	Wolf() {};
	~Wolf() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

