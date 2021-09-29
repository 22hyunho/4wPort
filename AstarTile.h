#pragma once
class AstarTile
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H 
	//F == 총 거리 비용 (TotalCost)
	//G == 시작점으로부터 현재 노드까지 경로비용(CostFromStart)
	//H == 현재노드로부터 도착점까지 경로비용(CostToGoal)

	float _totalCost;		//F
	float _costFromStart;	//G
	float _costToGoal;		//H

	bool _isOpen;//갈수있는 타일인지 유무

	AstarTile* _parentNode; //제일 상위 타일 (계속 갱신되는 타일)
	string _attribute;		//속성
public:
	AstarTile();
	~AstarTile();

	HRESULT init(int idX, int idY);

	//=====================접근자&설정자=====================
	int getIdX() { return _idX; }
	int getIdY() { return _idY; }

	POINT getCenter() { return _center; }
	RECT getRect() { return _rc; }

	float getTotalCost() { return _totalCost; }
	void setTotalCost(float F) { _totalCost = F; }

	float getCostFromStart() { return _costFromStart; }
	void setCostFromStart(float G) { _costFromStart = G; }

	float getCostToGoal() { return _costToGoal; }
	void setCostToGoal(float H) { _costToGoal = H; }

	bool getIsOpen() { return _isOpen; }
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }

	AstarTile* getParentNode() { return _parentNode; }
	void setParentNode(AstarTile* node) { _parentNode = node; }

	string getAttribute() { return _attribute; }
	void setAttribute(string attribute) { _attribute = attribute; }
};

