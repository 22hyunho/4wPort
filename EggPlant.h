#pragma once
#include "Artifact.h"
class EggPlant :
	public Artifact
{
private:

public:
	EggPlant() {};
	~EggPlant() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

