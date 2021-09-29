#pragma once
#include "Scene.h"
class gameOverScene :
	public Scene
{
private :

public :
	gameOverScene() {};
	~gameOverScene() {};

	HRESULT init(Player* player);
	void release();
	void update();
	void render();
	void changeScene();
};

