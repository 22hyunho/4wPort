#pragma once
#include "Food.h"
class Egg :
	public Food
{
private :

public :
	Egg() {};
	~Egg() {};

	virtual HRESULT init(Player* player);
};

