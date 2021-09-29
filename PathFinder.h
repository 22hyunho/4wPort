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
	//전체 타일 벡터
	PTILE _allTileList;
	int _mapWidth;
	int _mapHeight;

	//전체 타일 담을 벡터
	tileList	_vTotalList;
	tileIter	_viTotalList;

	//갈 수 있는 타일 담을 벡터
	tileList	_vOpenList;
	tileIter	_viOpenList;

	//가장 가까운 경로를 담을 벡터
	tileList	_vCloseList;
	tileIter	_viCloseList;

	//최종 경로
	tileList	_vPathList;

	//시작, 끝, 현재 타일
	AstarTile*		_startTile;
	AstarTile*		_endTile;
	AstarTile*		_currentTile;

public:
	PathFinder();
	~PathFinder();

	HRESULT init();
	void release();
	void update();

	//타일 셋팅 함수
	void setTiles(Enemy* startEnemy, Player* endPlayer = nullptr);
	//갈 수 있는 길을 찾아 담아줄 함수
	vector<AstarTile*> addOpenList(AstarTile* currentTile);
	//길 찾는 함수
	void findPath(AstarTile* currentTile);
	void resetPathList();

	//=====================접근자&설정자=====================

	tileList& getPathList() { return _vPathList; }
};

