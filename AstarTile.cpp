#include "stdafx.h"
#include "AstarTile.h"

AstarTile::AstarTile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),
	_idX(0), _idY(0), _isOpen(true)
{
}

AstarTile::~AstarTile()
{
}

HRESULT AstarTile::init(int idX, int idY)
{
	_idX = idX;												//몇번째 타일인지? idX + idY * 타일높이 == 몇번째타일
	_idY = idY;

	_center = PointMake(_idX * TILESIZE + (TILESIZE / 2),	//타일 센터좌표 설정
		_idY * TILESIZE + (TILESIZE / 2));
	
	_rc = RectMakeCenter(_idX * TILESIZE + (TILESIZE / 2), _idY * TILESIZE + (TILESIZE / 2), TILESIZE, TILESIZE);

	_totalCost = 0;			//F
	_costFromStart = 0;		//G
	_costToGoal = 0;		//H

	_isOpen = true;			//갈수있는 타일인지 유무

	_parentNode = nullptr;  //제일 상위 타일 (계속 갱신되는 타일)
	_attribute = "";

	return S_OK;
}
