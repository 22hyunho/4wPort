#pragma once
#include "Food.h"
class RabbitStew :
	public Food
{
private :

public :
	RabbitStew() {};
	~RabbitStew() {};

	virtual HRESULT init(Player* player);
};

