#pragma once
#include "Scene.h"
class bossRoom1 :
	public Scene
{
private :
	RECT _room;
	RECT _shadow;
	RECT _shadow2;
	dImage* _entrance;
	dImage* _exit;
	int _summonCount;
	int _state;

	float _alpha;
	float _alpha2;
	int _height;
	int _height2;
public :
	bossRoom1() {};
	~bossRoom1() {};

	HRESULT init(Player *player);
	void release();
	void update();
	void render();

	virtual void changeScene();
};

