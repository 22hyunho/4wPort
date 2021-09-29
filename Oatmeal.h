#pragma once
#include "Food.h"
class Oatmeal :
	public Food
{
private :

public :
	Oatmeal() {};
	~Oatmeal() {};

	virtual HRESULT init(Player* player);
};

