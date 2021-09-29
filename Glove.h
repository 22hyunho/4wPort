#pragma once
#include "Artifact.h"
class Glove :
	public Artifact
{
private :

public :
	Glove() {};
	~Glove() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();
};

