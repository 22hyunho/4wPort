#pragma once
#include "Artifact.h"
class Coffee :
	public Artifact
{
private:

public:
	Coffee() {};
	~Coffee() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

