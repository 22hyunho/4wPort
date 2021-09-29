#pragma once
#include "Scene.h"
class endScene :
	public Scene
{
private:

public:
	endScene() {};
	~endScene() {};

	HRESULT init(Player* player);
	void release();
	void update();
	void render();
	void changeScene();
};

