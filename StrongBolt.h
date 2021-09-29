#pragma once
#include "Artifact.h"
class StrongBolt :
	public Artifact
{

private:

public:
	StrongBolt() {};
	~StrongBolt() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

