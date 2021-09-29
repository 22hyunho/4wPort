#pragma once
#include "Effect.h"
class XbowEffect :
	public Effect
{
private:

public:
	XbowEffect() {};
	~XbowEffect() {};

	virtual HRESULT init(int frameX, int frameY, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

