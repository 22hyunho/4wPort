#pragma once
#include "Artifact.h"
class Tear :
	public Artifact
{
private:

public:
	Tear() {};
	~Tear() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

