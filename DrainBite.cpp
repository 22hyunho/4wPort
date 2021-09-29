#include "stdafx.h"
#include "DrainBite.h"
#include "Player.h"

HRESULT DrainBite::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("drainBite", L"img/artifact/drainBite1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"ÈíÇ÷ ÀÌ»¡";
	_info = L"ÀûÀ» Á×ÀÌ¸é È®·üÀûÀ¸·Î Ã¼·ÂÀÌ Áõ°¡ÇÑ´Ù.";
	_type = ART_DRAINBITE;

	return S_OK;
}

HRESULT DrainBite::init(Player * player)
{
	player->setDrain(true);
	return S_OK;
}

void DrainBite::release()
{
}

void DrainBite::update()
{
}

void DrainBite::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
