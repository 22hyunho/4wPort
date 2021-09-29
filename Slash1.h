#pragma once
#include "Effect.h"
class Slash1 :
	public Effect
{
private :

public:
	Slash1() {};
	~Slash1() {};

	virtual HRESULT init(float x, float y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
};

