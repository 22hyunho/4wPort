#pragma once
#include "Scene.h"
class bossRoom2 :
	public Scene
{
private:
	RECT _room;
	RECT _shadow;
	dImage* _entrance;

	float _alpha;
	int _height;

public:
	bossRoom2() {};
	~bossRoom2() {};

	HRESULT init(Player *player);
	void release();
	void update();
	void render();

	virtual void changeScene();
};

