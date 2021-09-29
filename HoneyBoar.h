#pragma once
#include "Food.h"
class HoneyBoar :
	public Food
{
private :
	
public :
	HoneyBoar() {};
	~HoneyBoar() {};

	virtual HRESULT init(Player* player);
};

