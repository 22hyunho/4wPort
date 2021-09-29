#pragma once
#include "gameNode.h"
#include "Player.h"

class playGround : public gameNode
{
private:
	bool _debug;
	Player* _player;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};