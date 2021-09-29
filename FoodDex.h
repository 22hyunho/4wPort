#pragma once
#include "singletonBase.h"
#include "Food.h"
#include <map>

class FoodDex : public singletonBase<FoodDex>
{
private :
	typedef map<int, Food*>				_foodList;
	typedef map<int, Food*>::iterator	_foodIter;

private:
	_foodList _mFood;
	_foodIter _miFood;

public:
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();			//�׸��� �Լ�

	Food* registerFood(int num, Food* food);

	Food* makeFood(int num);
};

