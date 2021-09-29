#include "stdafx.h"
#include "EggPlant.h"
#include "Player.h"

HRESULT EggPlant::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("eggPlant", L"img/artifact/eggPlant1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"������ ����";
	_info = L"���鶧 �� ���� �ʼ�. �ִ� ü���� �����Ѵ�.";
	_type = ART_EGGPLANT;

	return S_OK;
}

HRESULT EggPlant::init(Player * player)
{
	player->setMaxHP(player->getMaxHP() + 2);
	player->setCurrentHP(player->getMaxHP());
	return S_OK;
}

void EggPlant::release()
{
}

void EggPlant::update()
{
}

void EggPlant::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
