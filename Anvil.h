#pragma once
#include "Artifact.h"

class Anvil :
	public Artifact
{
private :

public :
	Anvil() {};
	~Anvil() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

