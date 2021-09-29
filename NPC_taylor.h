#pragma once
#include "NPC.h"
class NPC_taylor :
	public NPC
{
private:

public:
	NPC_taylor() {};
	~NPC_taylor() {};

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

