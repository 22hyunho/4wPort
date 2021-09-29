#pragma once
#include "Food.h"
class CabbageSoup :
	public Food
{
private :

public :
	CabbageSoup() {};
	~CabbageSoup() {};

	virtual HRESULT init(Player* player);
};

