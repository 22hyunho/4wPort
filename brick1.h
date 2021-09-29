#pragma once
#include "Scene.h"
class brick1 :
	public Scene
{
private :

public :
	brick1() {};
	~brick1() {};

	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
};

