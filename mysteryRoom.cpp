#include "stdafx.h"
#include "mysteryRoom.h"
#include "Player.h"

HRESULT mysteryRoom::init(Player *player)
{
	Scene::init(player);
	TILEMANAGER->load("mysteryRoom.map", 40, 30);
	CAMERAMANAGER->setBackScreenSize(TILESIZE * 40, TILESIZE * 30);

	_light = IMAGEMANAGER->addDImage("light", L"img/object/light2.png", 333, 140);

	_store.img = IMAGEMANAGER->addDImage("store", L"img/object/store2.png", 382, 224);
	_store.rc = RectMakeCenter(1110, 200, _store.img->getWidth(), _store.img->getHeight());
	_store.interact1 = RectMake(920, 275, 110, 60);
	_store.interact2 = RectMake(1060, 275, 100, 60);
	_store.interact3 = RectMake(1190, 275, 110, 60);

	_button.img = IMAGEMANAGER->addFrameDImage("button", L"img/object/button.png", 72, 39, 2, 1);
	_button.rc = RectMakeCenter(830, 370, _button.img->getFrameWidth(), _button.img->getFrameHeight());
	_button.interact1 = RectMakeCenter(830, 370, TILESIZE, TILESIZE);

	_frameX = 0;
	_number = 0;
	_gold = 5;

	_open = false;
	_visit++;

	_player->changeRune(_player->getDRune());
	_player->changeDRune(-_player->getDRune());

	TXTDATA->saveGame(_player);
	SOUNDMANAGER->play("brick");
	return S_OK;
}

void mysteryRoom::release()
{
}

void mysteryRoom::update()
{
	collision();
	interact();
	CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());
	TILEMANAGER->update();
	if (CAMERAMANAGER->getFade() >= 0) _player->update();

	RECT temp;
	if (ARTIFACTDEX->getVArtifact().size() > 0 && IntersectRect(&temp, &_player->getRect(), &ARTIFACTDEX->getVArtifact()[0]->getRect()))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			INVENTORY->addArtifact(ARTIFACTDEX->getVArtifact()[0]);
			ARTIFACTDEX->clearArtifact();
		}
	}

	if (ARTIFACTDEX->getVArtifact().size() > 0 && IntersectRect(&temp, &_player->getRect(), &ARTIFACTDEX->getVArtifact()[1]->getRect()))
	{
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			INVENTORY->addArtifact(ARTIFACTDEX->getVArtifact()[1]);
			ARTIFACTDEX->clearArtifact();
		}
	}

	if (ARTIFACTDEX->getVArtifact().size() > 0 && IntersectRect(&temp, &_player->getRect(), &ARTIFACTDEX->getVArtifact()[2]->getRect()))
	{
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			INVENTORY->addArtifact(ARTIFACTDEX->getVArtifact()[2]);
			ARTIFACTDEX->clearArtifact();
		}
	}
	changeScene();

}

void mysteryRoom::render()
{
	TILEMANAGER->render();
	_store.img->render(_store.rc.left, _store.rc.top);
	if (_open) _light->render(_store.rc.left + TILESIZE / 2, _store.rc.top + 38);
	_button.img->frameRender(_button.rc.left, _button.rc.top, _frameX, 0);
	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_store.rc);
		DTDMANAGER->Rectangle(_button.rc);
		DTDMANAGER->Rectangle(_store.interact1);
		DTDMANAGER->Rectangle(_store.interact2);
		DTDMANAGER->Rectangle(_store.interact3);
		DTDMANAGER->Rectangle(_button.interact1);
	}
	ARTIFACTDEX->render();

	RECT rc;
	if (ARTIFACTDEX->getVArtifact().size() > 0 && IntersectRect(&rc, &_player->getRect(), &_store.interact1))
	{
		DTDMANAGER->printText(ARTIFACTDEX->getVArtifact()[0]->getInfo().c_str(), 
			ARTIFACTDEX->getVArtifact()[0]->getRect().left + TILESIZE, ARTIFACTDEX->getVArtifact()[0]->getRect().top, 50, 20);
	}
	if (ARTIFACTDEX->getVArtifact().size() > 0 && IntersectRect(&rc, &_player->getRect(), &_store.interact2))
	{
		DTDMANAGER->printText(ARTIFACTDEX->getVArtifact()[1]->getInfo().c_str(), 
			ARTIFACTDEX->getVArtifact()[1]->getRect().left + TILESIZE, ARTIFACTDEX->getVArtifact()[1]->getRect().top, 50, 20);
	}
	if (ARTIFACTDEX->getVArtifact().size() > 0 && IntersectRect(&rc, &_player->getRect(), &_store.interact3))
	{
		DTDMANAGER->printText(ARTIFACTDEX->getVArtifact()[2]->getInfo().c_str(), 
			ARTIFACTDEX->getVArtifact()[2]->getRect().left + TILESIZE, ARTIFACTDEX->getVArtifact()[2]->getRect().top, 50, 20);
	}

	if (_open)
	{
		if (IntersectRect(&rc, &_player->getRect(), &_store.interact1))
		{
			_keyE->render(_store.interact1.left + 35, _store.interact1.top - TILESIZE * 2 - 20);
		}
		else if (IntersectRect(&rc, &_player->getRect(), &_store.interact2))
		{
			_keyE->render(_store.interact2.left + 25, _store.interact2.top - TILESIZE * 2 - 20);
		}
		else if (IntersectRect(&rc, &_player->getRect(), &_store.interact3))
		{
			_keyE->render(_store.interact3.left + 28, _store.interact3.top - TILESIZE * 2 - 20);
		}
	}

	else
	if (IntersectRect(&rc, &_player->getRect(), &_button.interact1))
	{
		_keyE->render(_button.rc.left - 5, _button.rc.top - TILESIZE * 2 + 10);

		WCHAR str[128];
		swprintf_s(str, L"필요한 골드 : %d", _index * _gold);
		DTDMANAGER->printText(str, _button.rc.left + 30, _button.rc.top - TILESIZE * 2, 150, 30);
	}
	_player->render();

	//WCHAR str[128];
	//swprintf_s(str, L"visit : %d", _visit);
	//DTDMANAGER->printText(str, 600, 600, 150, 30);
	EFFECTMANAGER->render();
}

void mysteryRoom::changeScene()
{
	RECT rc;
	for (int i = 0; i < TILEMANAGER->getWidth() * TILEMANAGER->getHeight(); i++)
	{
		if (TILEMANAGER->getTile()[i].obj == OBJ_STAIR &&
			IntersectRect(&rc, &_player->getRect(), &TILEMANAGER->getTile()[i].rc))
		{
			CAMERAMANAGER->setFade(FADEOUT);
			_player->downStair();
			if (CAMERAMANAGER->getAlpha() == 1.0) {
				//x, y 설정
				if (_visit == 1)
				{
					TILEMANAGER->release();
					SCENEMANAGER->changeScene("brick1");
					_player->inDungeon();
					_player->setX(2445);
					_player->setY(480);
				}
				else if (_visit == 2)
				{
					TILEMANAGER->release();
					SCENEMANAGER->changeScene("boss2");
					_player->inDungeon();
					_player->setX(360);
					_player->setY(2000);
					SOUNDMANAGER->stop("brick");
				}
			}
		}
	}
}

void mysteryRoom::interact()
{
	RECT rc;
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (IntersectRect(&rc, &_player->getRect(), &_button.interact1) && _player->getGold() >= _index * _gold)
		{
			_player->changeGold(-_index * _gold);
			_index++;
			int rnd[3];
			while (true)
			{
				for (int i = 0; i < 3; i++)
					rnd[i] = RND->getInt(11);

				if (rnd[1] == rnd[0]) continue;
				if (rnd[2] == rnd[0] || rnd[2] == rnd[1]) continue;
				break;
			}

			_open = true;

			ARTIFACTDEX->makeArtifact(_store.interact1.left + 55, _store.interact1.top, rnd[0]);
			ARTIFACTDEX->makeArtifact(_store.interact2.left + 47, _store.interact2.top, rnd[1]);
			ARTIFACTDEX->makeArtifact(_store.interact3.left + 48, _store.interact3.top, rnd[2]);
		}

		if (IntersectRect(&rc, &_player->getRect(), &_store.interact1) && _open)
		{
			INVENTORY->addArtifact(ARTIFACTDEX->getVArtifact()[0]);
			ARTIFACTDEX->clearArtifact();
			_open = false;
		}
		else if (IntersectRect(&rc, &_player->getRect(), &_store.interact2) && _open)
		{
			INVENTORY->addArtifact(ARTIFACTDEX->getVArtifact()[1]);
			ARTIFACTDEX->clearArtifact();
			_open = false;
		}
		else if (IntersectRect(&rc, &_player->getRect(), &_store.interact3) && _open)
		{
			INVENTORY->addArtifact(ARTIFACTDEX->getVArtifact()[2]);
			ARTIFACTDEX->clearArtifact();
			_open = false;
		}
	}
	if (_open)  _frameX = 1;
	else		_frameX = 0;
}

void mysteryRoom::collision()
{
	RECT rc;
	if (IntersectRect(&rc, &_player->getRect(), &_store.rc))
	{
		float width = rc.right - rc.left;
		float height = rc.bottom - rc.top;

		//좌우 충돌
		if (height > width) {
			//좌
			if (_player->getX() < (_store.rc.left + _store.rc.right) / 2) {
				_player->setX(_player->getX() - width);
			}
			//우
			else {
				_player->setX(_player->getX() + width);
			}
		}
		//상하 충돌
		else if (width > height) {
			//아래
			if (_player->getY() > (_store.rc.top + _store.rc.bottom) / 2)
			{
				_player->setY(_player->getY() + height);
			}
			//위
			else
			{
				_player->setY(_player->getY() - height);
			}
		}
		_player->setRect(_player->getX(), _player->getY(), TILESIZE / 2, TILESIZE);
	}

	if (IntersectRect(&rc, &_player->getRect(), &_button.rc))
	{
		float width = rc.right - rc.left;
		float height = rc.bottom - rc.top;

		//좌우 충돌
		if (height > width) {
			//좌
			if (_player->getX() < (_button.rc.left + _button.rc.right) / 2) {
				_player->setX(_player->getX() - width);
			}
			//우
			else {
				_player->setX(_player->getX() + width);
			}
		}
		//상하 충돌
		else if (width > height) {
			//아래
			if (_player->getY() > (_button.rc.top + _button.rc.bottom) / 2)
			{
				_player->setY(_player->getY() + height);
			}
			//위
			else
			{
				_player->setY(_player->getY() - height);
			}
		}
		_player->setRect(_player->getX(), _player->getY(), TILESIZE / 2, TILESIZE);
	}
}
