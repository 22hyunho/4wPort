#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);

	_player = new Player;
	_player->init();

	SCENEMANAGER->init(_player);
	SCENEMANAGER->changeScene("intro");
	COLLISIONMANAGER->init(_player);
	UIMANAGER->init(_player);
	PLAYERUI->init(_player);
	INVENTORY->init(_player);

	_debug = false;

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();

	//DIALOGMANAGER->release();
	//DIALOGMANAGER->releaseSingleton();
}


void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		_debug = !_debug;
		PRINTMANAGER->setDebug(_debug);
	}

	SCENEMANAGER->update();
	SOUNDMANAGER->update();
	EFFECTMANAGER->update();
	UIMANAGER->update();
}


void playGround::render()
{
	if (STREAMMANAGER->getCurrentVideo()) {
		if (STREAMMANAGER->getPosition() < STREAMMANAGER->getLength())
			return;
	}

	DTDMANAGER->beginDraw();
	//================���� �� ���̿� �� �׸��ô�==========================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	ITEMMANAGER->render();

	DTDMANAGER->endDraw();
	//==================================================================
	CAMERAMANAGER->render(0, 0);
	//DTDMANAGER->render(0, 0, WINSIZEX, WINSIZEY);
}