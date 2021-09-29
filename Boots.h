#pragma once
#include "Artifact.h"
class Boots :
	public Artifact
{
private:

public:
	Boots() {};
	~Boots() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

