#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
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

//메모리 해제는 여기다 하세요 제발
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
	//================제발 이 사이에 좀 그립시다==========================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	ITEMMANAGER->render();

	DTDMANAGER->endDraw();
	//==================================================================
	CAMERAMANAGER->render(0, 0);
	//DTDMANAGER->render(0, 0, WINSIZEX, WINSIZEY);
}