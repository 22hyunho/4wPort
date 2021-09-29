#include "stdafx.h"
#include "Tear.h"
#include "Player.h"

HRESULT Tear::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("tear", L"img/artifact/tear1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"�������� ����";
	_info = L"�������� ���� ����ִ�. ���ݷ��� �����Ѵ�.";
	_type = ART_TEAR;

	return S_OK;
}

HRESULT Tear::init(Player * player)
{
	player->changeDamage(20);
	return S_OK;
}

void Tear::release()
{
}

void Tear::update()
{
}

void Tear::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
