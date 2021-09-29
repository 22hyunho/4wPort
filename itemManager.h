#pragma once
#include "singletonBase.h"
#include "Item.h"

class itemManager : public singletonBase<itemManager>
{
private :
	typedef vector<Item*>			_itemList;
	typedef vector<Item*>::iterator	_itemIter;

private :
	_itemList _vItem;
	_itemIter _viItem;

public :
	itemManager() {};
	~itemManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void dropGold(float x, float y, float angle, int value);
	void dropRune(float x, float y, float angle, int value);
	void dropMeat(float x, float y, float angle, int value);

	void remove(int num);
	_itemList getVItem() { return _vItem; }
	_itemIter getVIItem() { return _viItem; }
};

