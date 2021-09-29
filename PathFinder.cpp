#include "stdafx.h"
#include "PathFinder.h"
#include "Player.h"
#include "Enemy.h"

PathFinder::PathFinder()
{
}

PathFinder::~PathFinder()
{
}

HRESULT PathFinder::init()
{
	_allTileList = TILEMANAGER->getTile();
	_mapWidth = TILEMANAGER->getWidth();
	_mapHeight = TILEMANAGER->getHeight();


	//전체타일노드 채워주기
	for (int i = 0; i < _mapHeight * _mapWidth; i++)
		_vTotalList.push_back(new AstarTile);

	return S_OK;
}

void PathFinder::release()
{
	//전체벡터 지워주기
	_viTotalList = _vTotalList.begin();
	for (; _viTotalList != _vTotalList.end();) {
		if (*_viTotalList)	SAFE_DELETE(*_viTotalList);
		_viTotalList = _vTotalList.erase(_viTotalList);
	}


	//벡터 클리어
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	_vPathList.clear();
}

void PathFinder::update()
{
	findPath(_currentTile);
}

void PathFinder::setTiles(Enemy * startEnemy, Player* endPlayer)
{
	//벡터 클리어
	_vOpenList.clear();
	_vCloseList.clear();
	_vPathList.clear();

	//시작지점, 목표지점 설정
	_startTile = new AstarTile;
	_startTile->init(startEnemy->getX() / TILESIZE, startEnemy->getY() / TILESIZE);

			
	if (_startTile->getIdX() == (int)endPlayer->getX() / TILESIZE && _startTile->getIdY() == (int)endPlayer->getY() / TILESIZE)
	{
		if (_allTileList[_startTile->getIdY() * _mapWidth + (_startTile->getIdX() + 1)].obj == OBJ_BLOCK ||
			_allTileList[_startTile->getIdY() * _mapWidth + (_startTile->getIdX() + 1)].terrain == TR_BLOCK)
		{
			_endTile = new AstarTile;
			_endTile->init(endPlayer->getX() / TILESIZE - 1, endPlayer->getY() / TILESIZE);
		}
		else
		{
			_endTile = new AstarTile;
			_endTile->init(endPlayer->getX() / TILESIZE + 1, endPlayer->getY() / TILESIZE);
		}
	}
	else
	{
		_endTile = new AstarTile;
		_endTile->init(endPlayer->getX() / TILESIZE, endPlayer->getY() / TILESIZE);
	}

	//타일 셋팅
	for (int i = 0; i < _mapHeight; i++) {
		for (int j = 0; j < _mapWidth; j++) {
			int index = i * _mapWidth + j;
			_vTotalList[index]->init(j, i);

			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				SAFE_DELETE(_startTile);
				_startTile = _vTotalList[index];
				_startTile->setAttribute("start");
				continue;
			}
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				SAFE_DELETE(_endTile);
				_endTile = _vTotalList[index];
				_endTile->setAttribute("end");
				continue;
			}
		}
	}

	//현재 타일은 시작타일로
	_currentTile = _startTile;
}

vector<AstarTile*> PathFinder::addOpenList(AstarTile * currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;
	int endX = currentTile->getIdX() + 1;
	int endY = currentTile->getIdY() + 1;

	//예외처리
	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= _mapWidth)
		endX = _mapWidth - 1;
	if (endY >= _mapHeight)
		endY = _mapHeight - 1;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			int index = i * _mapWidth + j;
			AstarTile* node = _vTotalList[index];

			//예외처리
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (_allTileList[index].obj == OBJ_BLOCK || _allTileList[index].terrain == TR_BLOCK) continue;

			//현재 타일 계속 갱신해준다
			node->setParentNode(_currentTile);

			//주변 타일을 검출하면서 체크했는지 유무를 알수있게 임의의 불값 선언
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//이미 있는 애다
				if (*_viOpenList == node)
				{
					addObj = false;	//추가하지마라
					break;
				}
			}

			//이미 체크된 애는 건너뛴다
			if (!addObj) continue;

			//갈수 있는 타일은 오픈리스트 벡터에 담아준다
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

void PathFinder::findPath(AstarTile * currentTile)
{
	//비교하기 쉽게 임의의 경로비용을 설정해둔다
	float tempTotalCost = 5000;
	AstarTile* tempTile = nullptr;

	//오픈리스트 벡터 안에서, 가장 빠른 경로를 뽑아낸다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H 값 연산
		_vOpenList[i]->setCostToGoal(
			abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) * TILESIZE +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY()) * TILESIZE);

		//
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//타일 중점 사이에 길이가 (타일사이즈)보다 크냐? 크면 대각선, 아니면 상하좌우
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 1.414 * TILESIZE : TILESIZE);

		//총 경로비용 == 갈 수 있는 타일 들 중에서 총 경로 비용들
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//그렇게 뽑아낸 총 경로비용들을 임의의 경로비용과 연산해서,
		//가장 작은 값을 계속 뽑아낸다
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}

	//목적지에 도달하면 중단
	if (tempTile->getAttribute() == "end") {

		_vPathList.push_back(_endTile);
		//최단 경로를 저장
		while (_currentTile->getParentNode() != NULL)
		{
			_vPathList.insert(_vPathList.begin(), _currentTile);
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}


	//최단 경로를 뽑아주자
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//뽑아낸 최단 경로는 오픈리스트에서 삭제시킨다
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//함수안에서 똑같은 함수를 호출 하는게 재귀함수
	//재귀함수는 반드시 주의할 게 있는데
	//한 번 호출시 Stack메모리가 쌓이는데, 1.2메가 이상 오버되면
	//스택오버플로우 현상이 생긴다
	findPath(_currentTile);
}

void PathFinder::resetPathList()
{
	_vPathList.clear();
}
