#pragma once
#include "maptool.h"
#include "Scene.h"

class mapToolScene : public Scene
{
private:
	Maptool* _maptool;
	int _width;
	int _height;
	int x;
	int y;
public:
	mapToolScene() {};
	~mapToolScene() {};

	HRESULT init(Player *player);
	void release();
	void update();
	void render();
	void changeScene();
};

