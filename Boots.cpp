#include "stdafx.h"
#include "Boots.h"
#include "Player.h"

HRESULT Boots::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("boots", L"img/artifact/boots1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"부츠";
	_info = L"공격속도와 이동속도가 증가한다.";
	_type = ART_BOOTS;

	return S_OK;
}

HRESULT Boots::init(Player * player)
{
	player->changeAtkSpd(10);
	player->changeSpeed(2);
	return S_OK;
}

void Boots::release()
{
}

void Boots::update()
{
}

void Boots::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
