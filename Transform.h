#pragma once
#include "Effect.h"
class Transform :
	public Effect
{
private:

public:
	Transform() {};
	~Transform() {};

	virtual HRESULT init(float x, float y, bool reverse);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

