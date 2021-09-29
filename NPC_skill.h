#pragma once
#include "NPC.h"
class NPC_skill :
	public NPC
{
private:

public:
	NPC_skill() {};
	~NPC_skill() {};

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

