#include "stdafx.h"
#include "trapManager.h"
#include "BearTrap.h"
#include "SlowTrap.h"

HRESULT trapManager::init()
{
	return S_OK;
}

void trapManager::release()
{
	for (_viTrap = _vTrap.begin(); _viTrap != _vTrap.end();)
	{
		if ((*_viTrap) != NULL)
		{
			(*_viTrap)->release();
			SAFE_DELETE(*_viTrap);
			_viTrap = _vTrap.erase(_viTrap);
		}
		else ++_viTrap;
	}
}

void trapManager::update()
{
	for (_viTrap = _vTrap.begin(); _viTrap != _vTrap.end();)
	{
		(*_viTrap)->update();

		if ((*_viTrap)->getType() == BEARTRAP && (*_viTrap)->getLevel() == 3)
		{
			if (_vTrap.size() > 2)
			{
				SAFE_DELETE(*_viTrap);
				_viTrap = _vTrap.erase(_viTrap);
				//(*_viArrow)->release();
			}
			else if ((*_viTrap)->getOff())
			{
				SAFE_DELETE(*_viTrap);
				_viTrap = _vTrap.erase(_viTrap);
				//(*_viArrow)->release();
			}
			else ++_viTrap;
		}
		else
		{
			if (_vTrap.size() > 1)
			{
				SAFE_DELETE(*_viTrap);
				_viTrap = _vTrap.erase(_viTrap);
				//(*_viArrow)->release();
			}
			else if ((*_viTrap)->getOff())
			{
				SAFE_DELETE(*_viTrap);
				_viTrap = _vTrap.erase(_viTrap);
				//(*_viArrow)->release();
			}
			else ++_viTrap;
		}
	}
}

void trapManager::render()
{
	for (_viTrap = _vTrap.begin(); _viTrap != _vTrap.end(); ++_viTrap)
	{
		(*_viTrap)->render();
	}
}

void trapManager::deployBearTrap(float x, float y, POINT point, int level)
{
	_bearTrap = new BearTrap;
	_bearTrap->init(x, y, point, level);
	_vTrap.push_back(_bearTrap);
}

void trapManager::deploySlowTrap(float x, float y, POINT point, int level)
{
	_slowTrap = new SlowTrap;
	_slowTrap->init(x, y, point, level);
	_vTrap.push_back(_slowTrap);
}
