#pragma once
#include "Arrow.h"

class arrowManager
{
private :

	typedef vector<Arrow*>				_arrowList;
	typedef vector<Arrow*>::iterator	_arrowIter;

private :

	_arrowList	_vArrow;
	_arrowIter	_viArrow;

	Arrow* _hunter;
	Arrow* _xbow;

public :
	arrowManager() {};
	~arrowManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void shootHunter(float x, float y, float angle);
	void shootXbow(float x, float y, float angle);

	//=====================접근자&설정자=====================

	_arrowList getVArrow() { return _vArrow; }
	_arrowIter getVIArrow() { return _viArrow; }
};

