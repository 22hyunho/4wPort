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


	//��üŸ�ϳ�� ä���ֱ�
	for (int i = 0; i < _mapHeight * _mapWidth; i++)
		_vTotalList.push_back(new AstarTile);

	return S_OK;
}

void PathFinder::release()
{
	//��ü���� �����ֱ�
	_viTotalList = _vTotalList.begin();
	for (; _viTotalList != _vTotalList.end();) {
		if (*_viTotalList)	SAFE_DELETE(*_viTotalList);
		_viTotalList = _vTotalList.erase(_viTotalList);
	}


	//���� Ŭ����
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
	//���� Ŭ����
	_vOpenList.clear();
	_vCloseList.clear();
	_vPathList.clear();

	//��������, ��ǥ���� ����
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

	//Ÿ�� ����
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

	//���� Ÿ���� ����Ÿ�Ϸ�
	_currentTile = _startTile;
}

vector<AstarTile*> PathFinder::addOpenList(AstarTile * currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;
	int endX = currentTile->getIdX() + 1;
	int endY = currentTile->getIdY() + 1;

	//����ó��
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

			//����ó��
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (_allTileList[index].obj == OBJ_BLOCK || _allTileList[index].terrain == TR_BLOCK) continue;

			//���� Ÿ�� ��� �������ش�
			node->setParentNode(_currentTile);

			//�ֺ� Ÿ���� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ� ����
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�̹� �ִ� �ִ�
				if (*_viOpenList == node)
				{
					addObj = false;	//�߰���������
					break;
				}
			}

			//�̹� üũ�� �ִ� �ǳʶڴ�
			if (!addObj) continue;

			//���� �ִ� Ÿ���� ���¸���Ʈ ���Ϳ� ����ش�
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

void PathFinder::findPath(AstarTile * currentTile)
{
	//���ϱ� ���� ������ ��κ���� �����صд�
	float tempTotalCost = 5000;
	AstarTile* tempTile = nullptr;

	//���¸���Ʈ ���� �ȿ���, ���� ���� ��θ� �̾Ƴ���
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H �� ����
		_vOpenList[i]->setCostToGoal(
			abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) * TILESIZE +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY()) * TILESIZE);

		//
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//Ÿ�� ���� ���̿� ���̰� (Ÿ�ϻ�����)���� ũ��? ũ�� �밢��, �ƴϸ� �����¿�
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 1.414 * TILESIZE : TILESIZE);

		//�� ��κ�� == �� �� �ִ� Ÿ�� �� �߿��� �� ��� ����
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//�׷��� �̾Ƴ� �� ��κ����� ������ ��κ��� �����ؼ�,
		//���� ���� ���� ��� �̾Ƴ���
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

	//�������� �����ϸ� �ߴ�
	if (tempTile->getAttribute() == "end") {

		_vPathList.push_back(_endTile);
		//�ִ� ��θ� ����
		while (_currentTile->getParentNode() != NULL)
		{
			_vPathList.insert(_vPathList.begin(), _currentTile);
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}


	//�ִ� ��θ� �̾�����
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//�̾Ƴ� �ִ� ��δ� ���¸���Ʈ���� ������Ų��
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//�Լ��ȿ��� �Ȱ��� �Լ��� ȣ�� �ϴ°� ����Լ�
	//����Լ��� �ݵ�� ������ �� �ִµ�
	//�� �� ȣ��� Stack�޸𸮰� ���̴µ�, 1.2�ް� �̻� �����Ǹ�
	//���ÿ����÷ο� ������ �����
	findPath(_currentTile);
}

void PathFinder::resetPathList()
{
	_vPathList.clear();
}
