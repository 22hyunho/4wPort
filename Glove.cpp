#include "stdafx.h"
#include "Glove.h"
#include "Player.h"

HRESULT Glove::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("glove", L"img/artifact/glove1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"헌터의 장갑";
	_info = L"빠른 속도로 활을 당긴다. 공격 속도가 증가한다.";
	_type = ART_GLOVE;

	return S_OK;
}

HRESULT Glove::init(Player * player)
{
	player->changeAtkSpd(10);
	return S_OK;
}

void Glove::release()
{
}

void Glove::update()
{
}

void Glove::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
