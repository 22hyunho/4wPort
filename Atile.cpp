#include "stdafx.h"
#include "Atile.h"

Atile::Atile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),
	_idX(0), _idY(0), _isOpen(true)
{
}

Atile::~Atile()
{
}

HRESULT Atile::init(int x, int y)
{
	_idX = x;
	_idY = y;

	_center = PointMake(_idX * TILEWIDTH + (TILEWIDTH / 2),
		_idY * TILEHEIGHT + (TILEHEIGHT / 2));

	_totalCost = 0;
	_costFromStart = 0;
	_costToGoal = 0;

	_isOpen = true;//갈수있는 타일인지 유무

	_parentNode = nullptr; //제일 상위 타일 (계속 갱신되는 타일)
	_attribute = "";

	return S_OK;
}