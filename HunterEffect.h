#pragma once
#include "Effect.h"
class HunterEffect :
	public Effect
{
private:

public:
	HunterEffect() {};
	~HunterEffect() {};

	virtual HRESULT init(int frameX, int frameY, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

