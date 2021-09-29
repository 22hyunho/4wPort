#include "stdafx.h"
#include "endScene.h"
#include "Player.h"

HRESULT endScene::init(Player* player)
{
	Scene::init(player);
	IMAGEMANAGER->addDImage("endGame", L"img/background/end.png", 1920, 1080);
	SOUNDMANAGER->play("title");
	return S_OK;
}

void endScene::release()
{
}

void endScene::update()
{
	if (CAMERAMANAGER->getFade() >= 0)changeScene();
}

void endScene::render()
{
	IMAGEMANAGER->findDImage("endGame")->render(0, 0);
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	DTDMANAGER->printText(L"던전 탐험 완료. Enter키를 누르면 마을로 돌아갑니다.",
		screen.left + 625, screen.top + 550, 1000, 200, 30);
}

void endScene::changeScene()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		CAMERAMANAGER->setFade(FADEOUT);
	}
	if (CAMERAMANAGER->getAlpha() == 1.0) {
		//x, y 설정
		SCENEMANAGER->changeScene("town");
		_player->inTown();
		_player->setDeath(false);
		_player->getCharacter()->changeState(ST_IDLE);
		INVENTORY->clearArtifact();
		SOUNDMANAGER->stop("title");
	}
}
