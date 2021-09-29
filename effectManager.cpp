#include "stdafx.h"
#include "effectManager.h"
#include "HunterEffect.h"
#include "XbowEffect.h"
#include "NullBox.h"
#include "Slash1.h"
#include "PotExplode.h"
#include "Transform.h"
#include "bossEffect1_2.h"
#include "bossEffect2_1.h"
#include "bossEffect2_2.h"

HRESULT effectManager::init()
{
	return E_NOTIMPL;
}

void effectManager::release()
{
}

void effectManager::update()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();)
	{
		(*_viEffect)->update();
		COLLISIONMANAGER->effectWithPlayer();

		if ((*_viEffect)->getOff() == true)
		{
			SAFE_DELETE(*_viEffect);
			_viEffect = _vEffect.erase(_viEffect);
		}
		else ++_viEffect;
	}
}

void effectManager::render()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render();
	}
}

void effectManager::addNullBox(float x, float y, int width, int height)
{
	Effect* nullBox = new NullBox;
	nullBox->init(x, y, width, height);
	_vEffect.push_back(nullBox);
}

void effectManager::addSlash(float x, float y, int width, int height)
{
	Effect* slash = new Slash1;
	slash->init(x, y, width, height);
	_vEffect.push_back(slash);
}

void effectManager::addPotExplode(float x, float y, int width, int height)
{
	Effect* pot = new PotExplode;
	pot->init(x, y, width, height);
	_vEffect.push_back(pot);
}

void effectManager::addTransform(float x, float y, bool reverse)
{
	Effect* trans = new Transform;
	trans->init(x, y, reverse);
	_vEffect.push_back(trans);
}

void effectManager::addAfterEffect(int frameX, int frameY, float x, float y)
{
	Effect* x_after = new XbowEffect;
	x_after->init(frameX, frameY, x, y);
	_vEffect.push_back(x_after);
}

void effectManager::addAfterEffect2(int frameX, int frameY, float x, float y)
{
	Effect* h_after = new HunterEffect;
	h_after->init(frameX, frameY, x, y);
	_vEffect.push_back(h_after);
}

void effectManager::addBossEffect1_2(float x, float y, int width, int height)
{
	Effect* boss1_2 = new bossEffect1_2;
	boss1_2->init(x, y, width, height);
	_vEffect.push_back(boss1_2);
}

void effectManager::addBossEffect2_1(float x, float y, bool reverse)
{
	Effect* boss2_1 = new bossEffect2_1;
	boss2_1->init(x, y, reverse);
	_vEffect.push_back(boss2_1);
}

void effectManager::addBossEffect2_2(float x, float y, bool reverse)
{
	Effect* boss2_2 = new bossEffect2_2;
	boss2_2->init(x, y, reverse);
	_vEffect.push_back(boss2_2);
}
