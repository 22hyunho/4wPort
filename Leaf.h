#pragma once
#include "Artifact.h"
class Leaf :
	public Artifact
{
private:

public:
	Leaf() {};
	~Leaf() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

