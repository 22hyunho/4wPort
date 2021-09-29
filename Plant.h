#pragma once
#include "Enemy.h"
class Plant :
	public Enemy
{
private :
	int _hurtCount;
	
public :
	Plant() {};
	~Plant() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

