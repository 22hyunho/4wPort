#include "stdafx.h"
#include "Leaf.h"
#include "Player.h"

HRESULT Leaf::init(float x, float y)
{
	Artifact::init(x, y);
	_img = IMAGEMANAGER->addDImage("leaf", L"img/artifact/leaf1.png", 90, 96);
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	_name = L"����";
	_info = L"���ο� ���� ���Ƴ���. �ΰ��� ȭ���� �߻��Ѵ�.";
	_type = ART_LEAF;

	return S_OK;
}

HRESULT Leaf::init(Player * player)
{
	player->setLeaf(true);
	return S_OK;
}

void Leaf::release()
{
}

void Leaf::update()
{
}

void Leaf::render()
{
	_img->render(_rc.left, _rc.top - 50);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);
}
