#pragma once
#include "Boss.h"
class Boss_halfElf :
	public Boss
{
private :
	dImage* _img;
	RECT _detection2;

	int _attackCount;
	int _coolDownCount;

	int _pattern;
	int _transformCount;
	int _dyingCount;
	bool _coolDown;
	bool _transform;
	bool _dying;

	int _rnd;
	int _rndCount;
	float _effectX, _effectY;
public :
	Boss_halfElf() {};
	~Boss_halfElf() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void controlFrame();
	void detection();

	virtual void changeState(BOSSSTATE state);
};

