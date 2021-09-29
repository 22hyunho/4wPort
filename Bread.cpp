#include "stdafx.h"
#include "Bread.h"
#include "Player.h"

HRESULT Bread::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("a_bread", L"img/artifact/bread1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"바게트";
	_info = L"음식을 먹으면 더 많은 체력을 회복한다.";
	_type = ART_BREAD;

	return S_OK;
}

HRESULT Bread::init(Player * player)
{
	player->setBread(true);
	return S_OK;
}

void Bread::release()
{
}

void Bread::update()
{
}

void Bread::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
