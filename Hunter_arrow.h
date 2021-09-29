#pragma once
#include "Arrow.h"
class Hunter_arrow :
	public Arrow
{
private :

public :
	Hunter_arrow() {};
	~Hunter_arrow() {};

	virtual HRESULT init(float x, float y, float angle);
	virtual void release();
	virtual void update();
	virtual void render();
	
	virtual void move();
};

