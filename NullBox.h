#pragma once
#include "Effect.h"
class NullBox :
	public Effect
{
private:

public:
	NullBox() {};
	~NullBox() {};

	virtual HRESULT init(float x, float y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();
};

