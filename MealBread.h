#pragma once
#include "Food.h"
class MealBread :
	public Food
{
private :

public :
	MealBread() {};
	~MealBread() {};

	virtual HRESULT init(Player* player);
};

