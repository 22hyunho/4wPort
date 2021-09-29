#pragma once
#include "NPC.h"
class NPC_blacksmith : public NPC
{
private:

public:
	NPC_blacksmith() {};
	~NPC_blacksmith() {};

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

