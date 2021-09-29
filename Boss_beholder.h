#pragma once
#include "Boss.h"
class Boss_beholder :
	public Boss
{
private :
	dImage* _bodyImg;
	dImage* _bodyFrame;
	dImage* _eyeFrame;
	RECT _detection2;

	int _eyeFrameX;
	int _attackCount;
	int _coolDownCount;
	bool _coolDown;

	int _tuningDead;
	PlasmaCannon* _plasma;

public :
	Boss_beholder() {};
	~Boss_beholder() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
	void detection();

	virtual void changeState(BOSSSTATE state);
};

