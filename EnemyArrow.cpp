#include "stdafx.h"
#include "EnemyArrow.h"

HRESULT PlasmaBall::init(float range, int bulletMax)
{
	_range = range;
	_arrowMax = bulletMax;
	_frameX = _frameY = 0;
	return S_OK;
}

void PlasmaBall::release()
{
}

void PlasmaBall::update()
{
	move();
	COLLISIONMANAGER->bulletWithPlayer(this);
}

void PlasmaBall::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); ++_viArrow)
	{
		_viArrow->img->frameRender(_viArrow->rc.left, _viArrow->rc.top, _frameX, _frameY);

		_viArrow->count++;

		if (_viArrow->count % 10 == 0)
		{
			if (_frameX >= _viArrow->img->getMaxFrameX())
				_frameX = 0;

			else
				_frameX++;

			_viArrow->count = 0;
		}
	}
}

void PlasmaBall::fire(float x, float y, float angle)
{
	if (_arrowMax < _vArrow.size()) return;
	tagArrow plasmaBall;
	ZeroMemory(&plasmaBall, sizeof(tagArrow));

	plasmaBall.img = new dImage;
	plasmaBall.img->init(L"img/effect/plasmaBall.png", 48, 24, 2, 1);
	plasmaBall.x = plasmaBall.fireX = x;
	plasmaBall.y = plasmaBall.fireY = y;
	plasmaBall.speed = 6.0f;
	plasmaBall.damage = 2;
	plasmaBall.angle = angle;
	plasmaBall.rc = RectMakeCenter(plasmaBall.x, plasmaBall.y, 24, 24);

	_vArrow.push_back(plasmaBall);
}

void PlasmaBall::move()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		_viArrow->x += cosf(_viArrow->angle) * _viArrow->speed;
		_viArrow->y += -sinf(_viArrow->angle) * _viArrow->speed;

		_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y, 24, 24);

		if (_range < getDistance(_viArrow->x, _viArrow->y, _viArrow->fireX, _viArrow->fireY))
		{
			_viArrow = _vArrow.erase(_viArrow);
			//SAFE_RELEASE(_viArrow->img);
			//SAFE_DELETE(_viArrow->img);
		}
		else ++_viArrow;
	}
}

void PlasmaBall::remove(int num)
{
	_vArrow[num].img->release();
	_vArrow.erase(_vArrow.begin() + num);
}



HRESULT PlasmaCannon::init(float range, int bulletMax)
{
	_range = range;
	_arrowMax = bulletMax;

	return S_OK;
}

void PlasmaCannon::release()
{
}

void PlasmaCannon::update()
{
	move();
	COLLISIONMANAGER->cannonWithPlayer(this);
}

void PlasmaCannon::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); ++_viArrow)
	{
		_viArrow->img->render(_viArrow->rc.left, _viArrow->rc.top);

		if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_viArrow->rc);
	}
}

void PlasmaCannon::fire(float x, float y, float angle)
{
	if (_arrowMax < _vArrow.size()) return;
	tagArrow plasmaCannon;
	ZeroMemory(&plasmaCannon, sizeof(tagArrow));

	plasmaCannon.img = new dImage;
	plasmaCannon.img->init(L"img/effect/bossEffect1_1.png", 155, 153);
	plasmaCannon.x = plasmaCannon.fireX = x;
	plasmaCannon.y = plasmaCannon.fireY = y;
	plasmaCannon.speed = 6.0f;
	plasmaCannon.angle = angle;
	plasmaCannon.rc = RectMakeCenter(plasmaCannon.x, plasmaCannon.y, TILESIZE * 3, TILESIZE * 3);

	_vArrow.push_back(plasmaCannon);
}

void PlasmaCannon::move()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		_viArrow->x += cosf(_viArrow->angle) * _viArrow->speed;
		_viArrow->y += -sinf(_viArrow->angle) * _viArrow->speed;

		_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y, TILESIZE * 3, TILESIZE * 3);

		if (_range < getDistance(_viArrow->x, _viArrow->y, _viArrow->fireX, _viArrow->fireY))
		{
			EFFECTMANAGER->addBossEffect1_2(_viArrow->x, _viArrow->y, 0, 0);
			_viArrow = _vArrow.erase(_viArrow);
		}
		else ++_viArrow;
	}
}

void PlasmaCannon::remove(int num)
{
	_vArrow[num].img->release();
	_vArrow.erase(_vArrow.begin() + num);
}

HRESULT SphereSpell::init(float range, int bulletMax)
{
	_range = range;
	_arrowMax = bulletMax;

	_frameX = 0;
	return S_OK;
}

void SphereSpell::release()
{
}

void SphereSpell::update()
{
	move();
	COLLISIONMANAGER->spellWithPlayer(this);
}

void SphereSpell::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); ++_viArrow)
	{
		_viArrow->img->frameRender(_viArrow->rc.left, _viArrow->rc.top, _frameX, 0);

		_viArrow->count++;

		if (_viArrow->count % 10 == 0)
		{
			if (_frameX >= _viArrow->img->getMaxFrameX())
				_frameX = 0;

			else
				_frameX++;

			_viArrow->count = 0;
		}
	}
}

void SphereSpell::fire(float x, float y, float angle)
{
	if (_arrowMax < _vArrow.size()) return;
	tagArrow sphereSpell;
	ZeroMemory(&sphereSpell, sizeof(tagArrow));

	sphereSpell.img = new dImage;
	sphereSpell.img->init(L"img/effect/sphereSpell.png", 52, 26, 2, 1);
	sphereSpell.x = sphereSpell.fireX = x;
	sphereSpell.y = sphereSpell.fireY = y;
	sphereSpell.speed = 7.5f;
	sphereSpell.angle = angle;
	sphereSpell.index = 0;
	sphereSpell.damage = 3;
	sphereSpell.rc = RectMakeCenter(sphereSpell.x, sphereSpell.y, 26, 26);

	_vArrow.push_back(sphereSpell);
}

void SphereSpell::move()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		_viArrow->x += cosf(_viArrow->angle) * _viArrow->speed;
		_viArrow->y += -sinf(_viArrow->angle) * _viArrow->speed;

		if (_viArrow->rc.left < 192)
		{
			_viArrow->angle = PI - _viArrow->angle;
			_viArrow->x = 192 + (_viArrow->rc.right - _viArrow->rc.left) / 2;
		}
		if (_viArrow->rc.right > 1488)
		{
			_viArrow->angle = PI - _viArrow->angle;
			_viArrow->x = 1488 - (_viArrow->rc.right - _viArrow->rc.left) / 2;
		}
		if (_viArrow->rc.top < 288)
		{
			_viArrow->angle = PI * 2 - _viArrow->angle;
			_viArrow->y = 288 + (_viArrow->rc.bottom - _viArrow->rc.top) / 2;
		}
		if (_viArrow->rc.bottom > 1056)
		{
			_viArrow->angle = PI * 2 - _viArrow->angle;
			_viArrow->y = 1056 - (_viArrow->rc.bottom - _viArrow->rc.top) / 2;
		}

		_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y, 26, 26);

		if (_viArrow->rc.left < 192 || _viArrow->rc.right > 1488 || _viArrow->rc.top < 288 || _viArrow->rc.bottom > 1056) 
			_viArrow->index++;

		if (_viArrow->index > 2)
		{
			SAFE_RELEASE(_viArrow->img);
			SAFE_DELETE(_viArrow->img);
			_viArrow = _vArrow.erase(_viArrow);
		}
		else ++_viArrow;
		//if (_range < getDistance(_viArrow->x, _viArrow->y, _viArrow->fireX, _viArrow->fireY))
		//{
		//	_viArrow = _vArrow.erase(_viArrow);
		//}
		//else ++_viArrow;
	}
}

void SphereSpell::remove(int num)
{
	_vArrow.erase(_vArrow.begin() + num);
}
