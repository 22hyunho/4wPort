#pragma once
#include "Effect.h"
class bossEffect1_2 :
	public Effect
{
private:

public:
	bossEffect1_2() {};
	~bossEffect1_2() {};

	virtual HRESULT init(float x, float y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

