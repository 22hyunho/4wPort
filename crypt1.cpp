#include "stdafx.h"
#include "crypt1.h"
#include "Player.h"

HRESULT crypt1::init(Player * player)
{
	Scene::init(player);

	CAMERAMANAGER->setBackScreenSize(TILESIZE * 100, TILESIZE * 100);

	TILEMANAGER->load("crypt1.map", 100, 100);

	_em = new enemyManager;
	_em->init();

	_em->setEnemy(EM_SKELETON, 3175, 3980, _player);
	_em->setEnemy(EM_SKELETON, 3175, 3825, _player);
	_em->setEnemy(EM_ARMORSKELETON, 3175, 4150, _player);

	_em->setEnemy(EM_SPIDERQUEEN, 1540, 4230, _player);
	_em->setEnemy(EM_ARMORSKELETON, 1200, 3880, _player);
	_em->setEnemy(EM_SKELETON, 850, 4080, _player);
	_em->setEnemy(EM_SKELETON, 530, 4270, _player);

	_em->setEnemy(EM_SPIDERQUEEN, 2350, 2195, _player);
	_em->setEnemy(EM_ARMORSKELETON, 2350, 2630, _player);
	_em->setEnemy(EM_SKELETON, 2350, 3080, _player);

	_em->setEnemy(EM_SPIDERQUEEN, 1060, 1440, _player);
	_em->setEnemy(EM_ARMORSKELETON, 675, 1395, _player);

	_em->setEnemy(EM_SKELETON, 620, 630, _player);
	_em->setEnemy(EM_SKELETON, 1150, 725, _player);

	COLLISIONMANAGER->init(_em);
	SOUNDMANAGER->play("crypt");
	return S_OK;
}

void crypt1::release()
{
}

void crypt1::update()
{
	TILEMANAGER->update();
	_em->update();
	if (CAMERAMANAGER->getFade() >= 0)_player->update();
	CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());

	changeScene();
}

void crypt1::render()
{
	TILEMANAGER->render();
	_em->render();
	_player->render();
}

void crypt1::changeScene()
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
				SCENEMANAGER->changeScene("mystery");
				_player->inTown();
				_player->setX(335);
				_player->setY(235);
				SOUNDMANAGER->stop("crypt");
			}
		}
	}
}
