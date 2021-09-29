#pragma once
#include "Enemy.h"
class Minion :
	public Enemy
{
private:
	PlasmaBall* _plasma;

public:
	Minion() {};
	~Minion() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void controlFrame();
	virtual void changeState(ENEMYSTATE state);
};

