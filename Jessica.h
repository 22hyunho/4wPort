#pragma once
#include "Character.h"
class Jessica :
	public Character
{
private :
	RECT _bowRc;
	float _bowX, _bowY;
	int _dodgeCount;
	int _bowFrameX;
	float _bowCount;

public :
	Jessica() {};
	~Jessica() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(float x, float y, float angle);

	void crossbowFrame();
	void addImage();
};

