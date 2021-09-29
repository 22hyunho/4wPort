#include "stdafx.h"
#include "Milk.h"
#include "Player.h"

HRESULT Milk::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("milk", L"img/artifact/milk1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"����";
	_info = L"���� § ���� ������. �ִ� ü���� �����Ѵ�.";
	_type = ART_MILK;

	return S_OK;
}

HRESULT Milk::init(Player * player)
{
	player->setMaxHP(player->getMaxHP() + 2);
	player->setCurrentHP(player->getMaxHP() + 2);
	return E_NOTIMPL;
}

void Milk::release()
{
}

void Milk::update()
{
}

void Milk::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
