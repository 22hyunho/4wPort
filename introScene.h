#pragma once
#include "Scene.h"
class introScene :
	public Scene
{
private:
	bool _change;

public:
	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void changeScene();
};

