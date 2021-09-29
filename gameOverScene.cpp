#include "stdafx.h"
#include "gameOverScene.h"
#include "Player.h"

HRESULT gameOverScene::init(Player* player)
{
	Scene::init(player);
	IMAGEMANAGER->addDImage("hunter_gameover", L"img/ui/hunter_gameOver.png", 171, 54);
	IMAGEMANAGER->addDImage("xbow_gameover", L"img/ui/xbow_gameOver.png", 108, 54);
	return S_OK;
}

void gameOverScene::release()
{
}

void gameOverScene::update()
{
	if (CAMERAMANAGER->getFade() >= 0)changeScene();
}

void gameOverScene::render()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	if (_player->getIndex() == CH_HUNTER) IMAGEMANAGER->findDImage("hunter_gameover")->render(screen.left + 450, screen.top + 350);
	else								  IMAGEMANAGER->findDImage("xbow_gameover")->render(screen.left + 450, screen.top + 350);
	DTDMANAGER->printText(L"당신은 죽었습니다. Enter키를 누르면 마을로 돌아갑니다.",
		screen.left + 600, screen.top + 550, 1000, 200, 30);
}

void gameOverScene::changeScene()
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
		_player->setGold(0);
		_player->setDRune(0);
		INVENTORY->clearArtifact();
		SOUNDMANAGER->stop("forest");
		SOUNDMANAGER->stop("brick");
		SOUNDMANAGER->stop("crypt");
		SOUNDMANAGER->stop("boss");
	}
}
