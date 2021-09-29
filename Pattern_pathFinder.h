#pragma once
#include "Pattern.h"
#include "PathFinder.h"

class AstarTile;

class Pattern_pathFinder :
	public Pattern
{
private :
	PathFinder* _pathFinder;
	vector <AstarTile*> _pathList;

public :
	Pattern_pathFinder() {};
	~Pattern_pathFinder() {};

	virtual HRESULT init(Player* player);
	virtual HRESULT init(Enemy* enemy);
	virtual void release();
	virtual void update();
	virtual void render();

	void detour();

	vector<AstarTile*> getPathList() { return _pathList; }
};

