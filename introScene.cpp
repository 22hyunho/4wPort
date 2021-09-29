#include "stdafx.h"
#include "introScene.h"

HRESULT introScene::init(Player * player)
{
	Scene::init(player);

	CAMERAMANAGER->setBackScreenSize(WINSIZEX, WINSIZEY);
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

	STREAMMANAGER->startVideo("intro", screen);

	_change = false;

	return S_OK;
}

void introScene::release()
{
	STREAMMANAGER->closeVideo();
}

void introScene::update()
{
	if (STREAMMANAGER->getPosition() >= STREAMMANAGER->getLength()) {

		STREAMMANAGER->closeVideo();

		D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

		STREAMMANAGER->startVideo("intro", screen);
	}

	changeScene();
}

void introScene::render()
{
}

void introScene::changeScene()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		STREAMMANAGER->closeVideo();
		CAMERAMANAGER->setFade(FADEOUT);
		_change = true;
	}

	if (_change) {
		if (CAMERAMANAGER->getAlpha() == 1.0)
			SCENEMANAGER->changeScene("title");
	}
}
