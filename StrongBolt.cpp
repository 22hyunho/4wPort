#include "stdafx.h"
#include "StrongBolt.h"
#include "Player.h"

HRESULT StrongBolt::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("strongBolt", L"img/artifact/strongBolt1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"강력한 볼트";
	_info = L"예리하게 만들어진 볼트이다. 공격력이 증가한다.";
	_type = ART_STRONGBOLT;

	return S_OK;
}

HRESULT StrongBolt::init(Player * player)
{
	player->changeDamage(20);
	return S_OK;
}

void StrongBolt::release()
{
}

void StrongBolt::update()
{
}

void StrongBolt::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
