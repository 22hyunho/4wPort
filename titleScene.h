#pragma once
#include "Scene.h"
class titleScene :
	public Scene
{
private:
	RECT _select[2];
	dImage* _back[4];
	dImage* _logo[2];
	dImage* _start;
	dImage* _quit;
	int _rnd;
public:
	titleScene() {};
	~titleScene() {};

	HRESULT init(Player* player);
	void release();
	void update();
	void render();
	void changeScene();
};

