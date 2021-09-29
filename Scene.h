#pragma once
#include <vector>
#include "enemyManager.h"
#include "Artifact.h"

class Player;

class Scene
{
protected:
	static Player* _player;
	enemyManager* _em;
	dImage* _keyE;
	int _hp;

	bool _isStart;
	bool _isEnd;
public:
	Scene() {};
	~Scene() {};

	virtual HRESULT init(Player* player);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void changeScene() = 0;

	bool getStart() { return _isStart; }
};