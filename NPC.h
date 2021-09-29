#pragma once

enum NPCLIST
{
	NPC_BLACKSMITH,
	NPC_COOK,
	NPC_TAYLOR,
	NPC_SKILL
};
class NPC
{
protected :
	RECT _rc;
	RECT _interactRc;
	dImage* _img;
	float _x, _y, _z;

public :
	NPC() {};
	~NPC() {};

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getRect() { return _rc; }
	RECT getInteractRect() { return _interactRc; }

	float getX() { return _x; }
	float getY() { return _y; }
};

