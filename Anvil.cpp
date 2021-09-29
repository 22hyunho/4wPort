#include "stdafx.h"
#include "Anvil.h"
#include "Player.h"

HRESULT Anvil::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("anvil", L"img/artifact/anvil1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"모루";
	_info = L"무기를 담금질해준다. 공격력이 증가한다.";
	_type = ART_ANVIL;

	return S_OK;
}

HRESULT Anvil::init(Player * player)
{
	player->changeDamage(20);
	return S_OK;
}

void Anvil::release()
{
}

void Anvil::update()
{
	//_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
}

void Anvil::render()
{
	_img->render(_rc.left, _rc.top - 50);


	if (PRINTMANAGER->isDebug())
	DTDMANAGER->Rectangle(_rc);
}
