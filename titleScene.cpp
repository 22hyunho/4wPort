#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(Player* player)
{
	Scene::init(player);
	CAMERAMANAGER->setBackScreenSize(WINSIZEX, WINSIZEY);
	CAMERAMANAGER->updateScreen(0, 0);
	CAMERAMANAGER->fadeOut();
	_back[0] = IMAGEMANAGER->addDImage("title1", L"img/background/back1.png", WINSIZEX, WINSIZEY);
	_back[1] = IMAGEMANAGER->addDImage("title2", L"img/background/back2.png", WINSIZEX, WINSIZEY);
	_back[2] = IMAGEMANAGER->addDImage("title3", L"img/background/back3.png", WINSIZEX, WINSIZEY);
	_back[3] = IMAGEMANAGER->addDImage("title4", L"img/background/back4.png", WINSIZEX, WINSIZEY);
	_logo[0] = IMAGEMANAGER->addDImage("logo1", L"img/background/manaSpark.png", 359, 237);
	_logo[1] = IMAGEMANAGER->addDImage("logo2", L"img/background/logo.png", 429, 190);
	_start = IMAGEMANAGER->addDImage("start", L"img/background/start.png", 57, 29);
	_quit = IMAGEMANAGER->addDImage("quit", L"img/background/quit.png", 81, 29);
	_rnd = RND->getInt(4);
	SOUNDMANAGER->play("title");
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	changeScene();
}

void titleScene::render()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_back[_rnd]->render(0, 0);
	_logo[0]->render(screen.right - 400, screen.top + 50);
	_logo[1]->render(screen.right - 430, screen.top + 190);
	_start->render(screen.right - 250, screen.top + 430);
	_quit->render(screen.right - 260, screen.top + 530);
	_select[0] = RectMake(screen.right - 250, screen.top + 430, _start->getWidth(), _start->getHeight());
	_select[1] = RectMake(screen.right - 260, screen.top + 530, _quit->getWidth(), _quit->getHeight());
}

void titleScene::changeScene()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_select[0], _ptMouse))
			CAMERAMANAGER->setFade(FADEOUT);
		
		else if (PtInRect(&_select[1], _ptMouse))
			PostQuitMessage(0);

	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		SCENEMANAGER->changeScene("maptool");
		SOUNDMANAGER->stop("title");
	}
		

	if (CAMERAMANAGER->getAlpha() == 1.0f)
	{
		SCENEMANAGER->changeScene("town");
		SOUNDMANAGER->stop("title");
	}
}
