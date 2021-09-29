#pragma once
#include "AstarTile.h"

class Player;
class Enemy;

class PathFinder :
	public AstarTile
{
private:
	typedef vector<AstarTile*>				tileList;
	typedef vector<AstarTile*>::iterator	tileIter;

private:
	//��ü Ÿ�� ����
	PTILE _allTileList;
	int _mapWidth;
	int _mapHeight;

	//��ü Ÿ�� ���� ����
	tileList	_vTotalList;
	tileIter	_viTotalList;

	//�� �� �ִ� Ÿ�� ���� ����
	tileList	_vOpenList;
	tileIter	_viOpenList;

	//���� ����� ��θ� ���� ����
	tileList	_vCloseList;
	tileIter	_viCloseList;

	//���� ���
	tileList	_vPathList;

	//����, ��, ���� Ÿ��
	AstarTile*		_startTile;
	AstarTile*		_endTile;
	AstarTile*		_currentTile;

public:
	PathFinder();
	~PathFinder();

	HRESULT init();
	void release();
	void update();

	//Ÿ�� ���� �Լ�
	void setTiles(Enemy* startEnemy, Player* endPlayer = nullptr);
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<AstarTile*> addOpenList(AstarTile* currentTile);
	//�� ã�� �Լ�
	void findPath(AstarTile* currentTile);
	void resetPathList();

	//=====================������&������=====================

	tileList& getPathList() { return _vPathList; }
};

