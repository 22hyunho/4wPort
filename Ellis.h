#pragma once
#include "Character.h"

class Ellis :
	public Character
{
private:
	RECT _bowRc;
	float _bowX, _bowY;
	int _dodgeCount;
	int _bowFrameX;
	int _aimFrameX;
	float _bowCount;

public:
	Ellis() {};
	~Ellis() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(float x, float y, float angle);

	void bowFrame();
	void addImage();
};

