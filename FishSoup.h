#pragma once
#include "Food.h"
class FishSoup :
	public Food
{
private :

public :
	FishSoup() {};
	~FishSoup() {};

	virtual HRESULT init(Player* player);
};

