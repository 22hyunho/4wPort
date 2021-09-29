#pragma once
#include "Scene.h"

struct tagObject
{
	dImage* img;
	RECT rc;
	RECT interact1;
	RECT interact2;
	RECT interact3;
};

class mysteryRoom :
	public Scene
{
private :
	dImage* _light;
	tagObject _store;
	tagObject _button;
	int _frameX;
	int _number;
	int _rnd[3];
	int _index;
	int _gold;

	int _visit;

	bool _open;
public :
	mysteryRoom() {};
	~mysteryRoom() {};

	virtual HRESULT init(Player *player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();
	
	void interact();
	void collision();
};

