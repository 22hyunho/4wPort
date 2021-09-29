#pragma once
#include "singletonBase.h"
#include "Artifact.h"
#include "Food.h"

class Player;

class Inventory : public singletonBase<Inventory>
{
private :
	typedef vector<Artifact*>				_artifactList;
	typedef vector<Artifact*>::iterator		_artifactIter;

	typedef vector<Food*>					_foodList;
	typedef vector<Food*>::iterator			_foodIter;

private :
	_artifactList	_vArtifact;
	_artifactIter	_viArtifact;

	_foodList		_vFood;
	_foodIter		_viFood;

	Player* _player;
public :
	Inventory() {};
	~Inventory() {};

	HRESULT init(Player* player);
	void release();
	void update();
	void render();

	void addArtifact(Artifact* artifact);
	void clearArtifact();
	void addFood(Food* food);
	void clearFoodList();

	//=====================접근자&설정자=====================
	_artifactList getVArtifact() { return _vArtifact; }
	_artifactIter getVIArtifact() { return _viArtifact; }

	_foodList getVFood() { return _vFood; }
	_foodIter getVIFood() { return _viFood; }
};

