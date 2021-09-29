#pragma once
#include "Artifact.h"
class DrainBite :
	public Artifact
{
private:

public:
	DrainBite() {};
	~DrainBite() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

