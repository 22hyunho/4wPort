#include "stdafx.h"
#include "arrowManager.h"
#include "Hunter_arrow.h"
#include "Xbow_bolt.h"

HRESULT arrowManager::init()
{
	return S_OK;
}

void arrowManager::release()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		if ((*_viArrow) != NULL)
		{
			(*_viArrow)->release();
			SAFE_DELETE(*_viArrow);
			_viArrow = _vArrow.erase(_viArrow);
		}
		else ++_viArrow;
	}

	_vArrow.clear();
}

void arrowManager::update()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		(*_viArrow)->update();

		if ((*_viArrow)->getOff() == true)
		{
			SAFE_DELETE(*_viArrow);
			_viArrow = _vArrow.erase(_viArrow);
			//(*_viArrow)->release();
		}
		else ++_viArrow;
	}
}

void arrowManager::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); ++_viArrow)
	{
		(*_viArrow)->render();
	}
}

void arrowManager::shootHunter(float x, float y, float angle)
{
	_hunter = new Hunter_arrow;
	_hunter->init(x, y, angle);
	_vArrow.push_back(_hunter);
}

void arrowManager::shootXbow(float x, float y, float angle)
{
	_xbow = new Xbow_bolt;
	_xbow->init(x, y, angle);
	_vArrow.push_back(_xbow);
}
