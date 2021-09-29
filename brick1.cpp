#include "stdafx.h"
#include "brick1.h"
#include "Player.h"

HRESULT brick1::init(Player * player)
{
	Scene::init(player);

	CAMERAMANAGER->setBackScreenSize(TILESIZE * 60, TILESIZE * 40);

	TILEMANAGER->load("brickDungeon.map", 60, 40);

	_em = new enemyManager;
	_em->init();

	_em->setEnemy(EM_ORC, 1465, 375, _player);
	_em->setEnemy(EM_ORCWARRIOR, 1405, 650, _player);
	_em->setEnemy(EM_ORC, 1220, 825, _player);
	_em->setEnemy(EM_SPIDER, 630, 900, _player);
	_em->setEnemy(EM_SPIDER, 220, 875, _player);
	_em->setEnemy(EM_ORC, 645, 425, _player);
	_em->setEnemy(EM_SPIDER, 350, 1560, _player);
	_em->setEnemy(EM_ORCWARRIOR, 1500, 1425, _player);
	_em->setEnemy(EM_ORCWARRIOR, 2000, 1450, _player);

	COLLISIONMANAGER->init(_em);

	//SOUNDMANAGER->play("brick");
	return S_OK;
}

void brick1::release()
{
}

void brick1::update()
{
	TILEMANAGER->update();
	_em->update();
	if (CAMERAMANAGER->getFade() >= 0)_player->update();
	CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());

	changeScene();
}

void brick1::render()
{
	TILEMANAGER->render();
	_em->render();
	_player->render();
}

void brick1::changeScene()
{
	RECT rc;
	for (int i = 0; i < TILEMANAGER->getWidth() * TILEMANAGER->getHeight(); i++)
	{
		if (TILEMANAGER->getTile()[i].obj == OBJ_STAIR &&
			IntersectRect(&rc, &_player->getRect(), &TILEMANAGER->getTile()[i].rc))
		{
			CAMERAMANAGER->setFade(FADEOUT);
			_player->downStair();
			if (CAMERAMANAGER->getAlpha() == 1.0)
			{
				SCENEMANAGER->changeScene("boss1");
				_player->inDungeon();
				_player->setX(960);
				_player->setY(2450);
				SOUNDMANAGER->stop("brick");
			}
		}
	}
}
