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
	_idX = idX;												//���° Ÿ������? idX + idY * Ÿ�ϳ��� == ���°Ÿ��
	_idY = idY;

	_center = PointMake(_idX * TILESIZE + (TILESIZE / 2),	//Ÿ�� ������ǥ ����
		_idY * TILESIZE + (TILESIZE / 2));
	
	_rc = RectMakeCenter(_idX * TILESIZE + (TILESIZE / 2), _idY * TILESIZE + (TILESIZE / 2), TILESIZE, TILESIZE);

	_totalCost = 0;			//F
	_costFromStart = 0;		//G
	_costToGoal = 0;		//H

	_isOpen = true;			//�����ִ� Ÿ������ ����

	_parentNode = nullptr;  //���� ���� Ÿ�� (��� ���ŵǴ� Ÿ��)
	_attribute = "";

	return S_OK;
}
