#include "stdafx.h"
#include "forest1.h"
#include "Player.h"

HRESULT forest1::init(Player * player)
{
	Scene::init(player);
	CAMERAMANAGER->setBackScreenSize(TILESIZE * 50, TILESIZE * 50);

	TILEMANAGER->load("forest1.map", 50, 50);

	_em = new enemyManager;
	_em->init();

	_em->setEnemy(EM_BAT, 1000, 445, _player);
	_em->setEnemy(EM_BAT, 1500, 630, _player);
	_em->setEnemy(EM_BAT, 2100, 430, _player);
	_em->setEnemy(EM_BAT, 1530, 230, _player);

	_em->setEnemy(EM_WOLF, 460, 1080, _player);
	_em->setEnemy(EM_PLANT, 680, 1360, _player);
	_em->setEnemy(EM_WOLF, 700, 1600, _player);

	_em->setEnemy(EM_WOLF, 1220, 1840, _player);
	_em->setEnemy(EM_PLANT, 1230, 1480, _player);

	_em->setEnemy(EM_PLANT, 1850, 1560, _player);

	COLLISIONMANAGER->init(_em);
	SOUNDMANAGER->play("forest");
	return S_OK;
}

void forest1::release()
{
}

void forest1::update()
{
	if (KEYMANAGER->isOnceKeyDown('K'))
		_player->setLeaf(true);
	TILEMANAGER->update();
	if (CAMERAMANAGER->getFade() >= 0) _player->update();
	_em->update();
	CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());

	changeScene();
}

void forest1::render()
{
	TILEMANAGER->render();
	_em->render();
	_player->render();
}

void forest1::changeScene()
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
				//x, y ¼³Á¤
				TILEMANAGER->release();
				SCENEMANAGER->changeScene("mystery");
				_player->inTown();
				_player->setX(335);
				_player->setY(235);
				SOUNDMANAGER->stop("forest");
			}
		}
	}
}
