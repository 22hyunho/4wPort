#include "stdafx.h"
#include "Glove.h"
#include "Player.h"

HRESULT Glove::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("glove", L"img/artifact/glove1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"������ �尩";
	_info = L"���� �ӵ��� Ȱ�� ����. ���� �ӵ��� �����Ѵ�.";
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
