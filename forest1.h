#pragma once
#include "Scene.h"
class forest1 :
	public Scene
{
private :
	RECT _downStair;

public :
	forest1() {};
	~forest1() {};

	HRESULT init(Player *player);
	void release();
	void update();
	void render();
	void changeScene();
};

