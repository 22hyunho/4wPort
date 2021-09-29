#include "stdafx.h"
#include "Inventory.h"
#include "Player.h"

HRESULT Inventory::init(Player* player)
{
	_player = player;
	return S_OK;
}

void Inventory::release()
{
	for (_viArtifact = _vArtifact.begin(); _viArtifact != _vArtifact.end();)
	{
		if ((*_viArtifact) != NULL) {
			//(*_viArtifact)->release();
			SAFE_DELETE((*_viArtifact));
			_viArtifact = _vArtifact.erase(_viArtifact);
		}
		else ++_viArtifact;
	}

	for (_viFood = _vFood.begin(); _viFood != _vFood.end();)
	{
		if ((*_viFood) != NULL) {
			//(*_viArtifact)->release();
			//SAFE_DELETE((*_viFood));
			_viFood = _vFood.erase(_viFood);
		}
		else ++_viFood;
	}

	_vArtifact.clear();
	_vFood.clear();
}

void Inventory::update()
{
	for (_viArtifact = _vArtifact.begin(); _viArtifact != _vArtifact.end(); ++_viArtifact)
	{
		(*_viArtifact)->update();
	}
	for (_viFood = _vFood.begin(); _viFood != _vFood.end(); ++_viFood)
	{
		(*_viFood)->update();
	}
}

void Inventory::render()
{
}

void Inventory::addArtifact(Artifact * artifact)
{
	artifact->init(_player);
	_vArtifact.push_back(artifact);
}

void Inventory::clearArtifact()
{
	_vArtifact.clear();
	_player->resetHP();
	_player->resetDamage();
	_player->resetAtkSpd();
	_player->resetSpeed();
	_player->setBread(false);
	_player->setLeaf(false);
	_player->setDrain(false);
}

void Inventory::addFood(Food * food)
{
	food->init(_player);
	_vFood.push_back(food);
}

void Inventory::clearFoodList()
{
	_vFood.clear();
	_player->resetBaseHP();
	_player->resetBaseDmg();
	_player->resetBaseAts();
	_player->setChance(false);
	_player->resetHP();
	_player->resetDamage();
	_player->resetAtkSpd();
}
