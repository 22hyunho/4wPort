#pragma once
#include "Arrow.h"
class Xbow_bolt :
	public Arrow
{
private:

public:
	Xbow_bolt() {};
	~Xbow_bolt() {};

	virtual HRESULT init(float x, float y, float angle);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
};

