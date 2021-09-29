#pragma once
#include "Scene.h"
class crypt1 :
	public Scene
{
private:

public:
	crypt1() {};
	~crypt1() {};

	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
};

