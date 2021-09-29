#include "stdafx.h"
#include "Coffee.h"
#include "Player.h"

HRESULT Coffee::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("coffee", L"img/artifact/coffee1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"Ŀ��";
	_info = L"���ݼӵ��� ũ�� ���������� �ִ� ü���� �����Ѵ�.";
	_type = ART_COFFEE;

	return S_OK;
}

HRESULT Coffee::init(Player * player)
{
	player->changeAtkSpd(15);
	if (player->getMaxHP() > 2)
	{
		player->setMaxHP(player->getMaxHP() - 2);
		player->setCurrentHP(player->getMaxHP());
	}
	else
	{
		player->setMaxHP(2);
		player->setCurrentHP(player->getMaxHP());
	}
	return S_OK;
}

void Coffee::release()
{
}

void Coffee::update()
{
}

void Coffee::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
