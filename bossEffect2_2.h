#pragma once
#include "Effect.h"
class bossEffect2_2 :
	public Effect
{
private:

public:
	bossEffect2_2() {};
	~bossEffect2_2() {};

	virtual HRESULT init(float x, float y, bool reverse);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

