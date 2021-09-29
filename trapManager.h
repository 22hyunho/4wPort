#pragma once
#include "Trap.h"
class trapManager
{
private:

	typedef vector<Trap*>				_trapList;
	typedef vector<Trap*>::iterator		_trapIter;

private:

	_trapList	_vTrap;
	_trapIter	_viTrap;

	Trap* _bearTrap;
	Trap* _slowTrap;

public:
	trapManager() {};
	~trapManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void deployBearTrap(float x, float y, POINT point, int level);
	void deploySlowTrap(float x, float y, POINT point, int level);

	//=====================접근자&설정자=====================

	_trapList getVTrap() { return _vTrap; }
	_trapIter getVITrap() { return _viTrap; }
};

