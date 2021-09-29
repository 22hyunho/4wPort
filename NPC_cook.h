#pragma once
#include "NPC.h"
class NPC_cook :
	public NPC
{
private :

public :
	NPC_cook() {};
	~NPC_cook() {};

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

