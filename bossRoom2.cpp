#include "stdafx.h"
#include "bossRoom2.h"
#include "Player.h"

HRESULT bossRoom2::init(Player * player)
{
	TILEMANAGER->load("boss2.map", 35, 50);
	CAMERAMANAGER->setBackScreenSize(TILESIZE * 35, TILESIZE * 50);
	IMAGEMANAGER->addDImage("shadow", L"img/object/dungeonDoor_shadow.png", 192, 24);
	_entrance = IMAGEMANAGER->addDImage("entrance1", L"img/object/dungeonDoor_width.png", 192, 156);

	_em = new enemyManager;
	_em->init();

	_em->setBoss(B_HALFELF, 795, 670, _player);

	_isStart = false;
	_room = RectMake(TILESIZE * 4, TILESIZE * 6, TILESIZE * 27, TILESIZE * 16);

	_shadow = RectMake(TILESIZE * 22, TILESIZE * 22, TILESIZE * 4, 24);
	_height = TILESIZE * 18;
	_alpha = 0.5f;

	COLLISIONMANAGER->init(_em);

	SOUNDMANAGER->play("boss");
	return S_OK;
}

void bossRoom2::release()
{
}

void bossRoom2::update()
{
	TILEMANAGER->update();
	_em->update();
	if (CAMERAMANAGER->getFade() >= 0) _player->update();
	CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());

	RECT rc;
	if (IntersectRect(&rc, &_player->getRect(), &_room))
	{
		_isStart = true;
	}

	for (int i = 0; i < _em->getVBoss().size(); i++)
	{
		_hp = ((float)_em->getVBoss()[i]->getCurrentHP() / (float)_em->getVBoss()[i]->getMaxHP()) * 695;
	}

	if (_isStart)
	{
		if (_height >= TILESIZE * 20 - 24)
		{
			_height += 0;
			_alpha = 1.f;
		}
		else
		{
			_height += 2;
			_alpha = 0.5f;
		}
		RECT rc;
		if (IntersectRect(&rc, &_player->getRect(), &_shadow))
		{
			_player->setY(_player->getY() - (rc.bottom - rc.top));
		}
	}

	changeScene();
}

void bossRoom2::render()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	TILEMANAGER->render();
	_em->render();
	_player->render();

	if (_isStart)
	{
		IMAGEMANAGER->findDImage("bossHP_bot")->render(screen.left + 145, screen.bottom - 90, 0, 0, _hp, 45);
		IMAGEMANAGER->findDImage("bossHP_top")->render(screen.left + 120, screen.bottom - 100);
	}

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_room);
	}
	IMAGEMANAGER->findDImage("shadow")->render(_shadow.left, _shadow.top, 0.3f);
	_entrance->render(TILESIZE * 22, _height, _alpha);
}

void bossRoom2::changeScene()
{
	if (_em->getVBoss()[0]->getDeath())
	{
		CAMERAMANAGER->setFade(FADEOUT);
		if (CAMERAMANAGER->getAlpha() == 1.0)
		{
			SCENEMANAGER->changeScene("end");
			_player->changeRune(_player->getDRune());
			_player->changeDRune(-_player->getDRune());
			TXTDATA->saveGame(_player);
			SOUNDMANAGER->stop("boss");
		}
	}
}
