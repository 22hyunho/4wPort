#pragma once
#include "tileInfo.h"

class Atile
{
private:
	int _idX;
	int _idY;

	POINT _center;

	//F = G + H 
	//F == 총 거리 비용 (TotalCost)
	//G == 시작점으로부터 현재 노드까지 경로비용(CostFromStart)
	//H == 현재노드로부터 도착점까지 경로비용(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;//갈수있는 타일인지 유무

	Atile* _parentNode; //제일 상위 타일 (계속 갱신되는 타일)
	string _attribute;

public:
	Atile();
	~Atile();

	HRESULT init(int x, int y);

	//============ 편리를 위한 접근자 & 설정자 ===============

	int getIdX() { return _idX; }
	void setIdX(int x) { _idX = x; }
	int getIdY() { return _idY; }
	void setIdY(int y) { _idY = y; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(Atile* t) { _parentNode = t; }
	Atile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};

