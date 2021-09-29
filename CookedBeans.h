#pragma once
#include "Food.h"
class CookedBeans :
	public Food
{
private:

public:
	CookedBeans() {};
	~CookedBeans() {};

	virtual HRESULT init(Player* player);
};

