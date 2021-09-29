#pragma once
class AstarTile
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H 
	//F == �� �Ÿ� ��� (TotalCost)
	//G == ���������κ��� ���� ������ ��κ��(CostFromStart)
	//H == ������κ��� ���������� ��κ��(CostToGoal)

	float _totalCost;		//F
	float _costFromStart;	//G
	float _costToGoal;		//H

	bool _isOpen;//�����ִ� Ÿ������ ����

	AstarTile* _parentNode; //���� ���� Ÿ�� (��� ���ŵǴ� Ÿ��)
	string _attribute;		//�Ӽ�
public:
	AstarTile();
	~AstarTile();

	HRESULT init(int idX, int idY);

	//=====================������&������=====================
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

