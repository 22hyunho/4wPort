#pragma once
#include "Effect.h"
class PotExplode :
	public Effect
{
private:

public:
	PotExplode() {};
	~PotExplode() {};

	virtual HRESULT init(float x, float y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

