#pragma once
#include "Artifact.h"
class Milk :
	public Artifact
{
private:

public:
	Milk() {};
	~Milk() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

