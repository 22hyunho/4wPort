#pragma once
#include "Pattern.h"
class Pattern_default :
	public Pattern
{
private :

public :
	Pattern_default() {};
	~Pattern_default() {};

	virtual HRESULT init(Player* player);
	virtual HRESULT init(Enemy* enemy);
	virtual void release();
	virtual void update();
	virtual void render();
};

