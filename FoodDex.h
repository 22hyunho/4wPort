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
	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();			//그리기 함수

	Food* registerFood(int num, Food* food);

	Food* makeFood(int num);
};

