#pragma once
#include "Artifact.h"
class Bread :
	public Artifact
{
private:

public:
	Bread() {};
	~Bread() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

