#include "stdafx.h"
#include "itemManager.h"
#include "Gold.h"
#include "Rune.h"
#include "Meat.h"

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::release()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		if ((*_viItem) != NULL)
		{
			(*_viItem)->release();
			SAFE_DELETE(*_viItem);
			_viItem = _vItem.erase(_viItem);
		}
		else ++_viItem;
	}
	_vItem.clear();
}

void itemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}
}

void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
		(*_viItem)->render();
}

void itemManager::dropGold(float x, float y, float angle, int value)
{
	Item* gold = new Gold;
	gold->init(x, y, angle, value);

	_vItem.push_back(gold);
}

void itemManager::dropRune(float x, float y, float angle, int value)
{
	Item* rune = new Rune;
	rune->init(x, y, angle, value);

	_vItem.push_back(rune);
}

void itemManager::dropMeat(float x, float y, float angle, int value)
{
	Item* meat = new Meat;
	meat->init(x, y, angle, value);

	_vItem.push_back(meat);
}

void itemManager::remove(int num)
{
	_vItem.erase(_vItem.begin() + num);
}
