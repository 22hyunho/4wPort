#include "stdafx.h"
#include "ArtifactDex.h"
#include "ArtifactHeader.h"

HRESULT ArtifactDex::init()
{
	registerArtifact(ART_ANVIL, new Anvil);
	registerArtifact(ART_BOOTS, new Boots);
	registerArtifact(ART_BREAD, new Bread);
	registerArtifact(ART_COFFEE, new Coffee);
	registerArtifact(ART_DRAINBITE, new DrainBite);
	registerArtifact(ART_EGGPLANT, new EggPlant);
	registerArtifact(ART_GLOVE, new Glove);
	registerArtifact(ART_LEAF, new Leaf);
	registerArtifact(ART_MILK, new Milk);
	registerArtifact(ART_STRONGBOLT, new StrongBolt);
	registerArtifact(ART_TEAR, new Tear);
	return S_OK;
}

void ArtifactDex::release()
{
	for (_viArtifact = _vArtifact.begin(); _viArtifact != _vArtifact.end();) 
	{
		if ((*_viArtifact) != NULL) {
			(*_viArtifact)->release();
			SAFE_DELETE((*_viArtifact));
			_viArtifact = _vArtifact.erase(_viArtifact);
		}
		else ++_viArtifact;
	}

	_vArtifact.clear();
}

void ArtifactDex::update()
{
	//for (_viArtifact = _vArtifact.begin(); _viArtifact != _vArtifact.end(); ++_viArtifact) 
	//{
	//	(*_viArtifact)->update();
	//}
}

void ArtifactDex::render()
{
	for (_viArtifact = _vArtifact.begin(); _viArtifact != _vArtifact.end(); ++_viArtifact)
	{
		(*_viArtifact)->render();
	}
}

Artifact * ArtifactDex::registerArtifact(int num, Artifact * artifact)
{
	if (!artifact) return nullptr;

	_mArtifact.insert(make_pair(num, artifact));

	return artifact;
}

HRESULT ArtifactDex::makeArtifact(float x, float y, int num)
{
	_miArtifact = _mArtifact.find(num);

	if (_miArtifact == _mArtifact.end()) return E_FAIL;

	//맵 컨테이너에 등록한 아티팩트를 찾아 벡터에 적재
	if (SUCCEEDED(_miArtifact->second->init(x, y))) {
		_vArtifact.push_back(_miArtifact->second);

		return S_OK;
	}

	return E_FAIL;
}

void ArtifactDex::removeArtifact(int num)
{
	_vArtifact.erase(_vArtifact.begin() + num);
}

void ArtifactDex::clearArtifact()
{
	_vArtifact.clear();
}
