#pragma once
#include "Effect.h"
class bossEffect2_1 :
	public Effect
{
private:
public:
	bossEffect2_1() {};
	~bossEffect2_1() {};

	virtual HRESULT init(float x, float y, bool reverse);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

