#include "stdafx.h"
#include "bossRoom1.h"
#include "Player.h"

HRESULT bossRoom1::init(Player * player)
{
	Scene::init(player);
	IMAGEMANAGER->addDImage("shadow", L"img/object/dungeonDoor_shadow.png", 192, 24);
	_entrance = IMAGEMANAGER->addDImage("entrance", L"img/object/dungeonDoor_width.png", 192, 156);
	_exit = IMAGEMANAGER->addDImage("exit", L"img/object/lockDoor_width.png", 192, 156);

	TILEMANAGER->load("boss1.map", 40, 60);
	CAMERAMANAGER->setBackScreenSize(TILESIZE * 40, TILESIZE * 60);

	_em = new enemyManager;
	_em->init();

	_em->setBoss(B_BEHOLDER, 960, 815, _player);
	//_em->setEnemy(EM_MINION, 900, 815, _player);
	//_em->setEnemy(EM_MINION, 1020, 815, _player);

	COLLISIONMANAGER->init(_em);
	_room = RectMakeCenter(960, 815, TILESIZE * 32, TILESIZE * 20);
	_isStart = false;
	_isEnd = false;
	_hp = 0;

	_alpha = 0.5f;
	_alpha2 = 1.f;
	_height = TILESIZE * 24;
	_height2 = TILESIZE * 8;
	_shadow = RectMake(TILESIZE * 18, TILESIZE * 28, TILESIZE * 4, 24);
	_shadow2 = RectMake(TILESIZE * 18, TILESIZE * 10 + 24, TILESIZE * 4, 24);

	_summonCount = 0;
	SOUNDMANAGER->play("boss");
	return S_OK;
}

void bossRoom1::release()
{
}

void bossRoom1::update()
{
	TILEMANAGER->update();
	CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());
	_player->update();
	_em->update();

	RECT rc;
	if (IntersectRect(&rc, &_player->getRect(), &_room))
	{
		_isStart = true;
	}

	if (_isStart)
	{
		if (_height >= TILESIZE * 26 - 24)
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
	if (_isStart && !_isEnd)
	{
		if (_em->getVEnemy().size() > 0)
			_summonCount = 0;

		else
			_summonCount++;

		if (_summonCount > 1000)
		{
			_em->setEnemy(EM_MINION, 900, 815, _player);
			_em->setEnemy(EM_MINION, 1020, 815, _player);

			_summonCount = 0;
		}
	}

	if (_em->getVBoss()[0]->getDeath()) _isEnd = true;

	if (!_isEnd)
	{
		RECT rc;
		if (IntersectRect(&rc, &_player->getRect(), &_shadow2))
		{
			_player->setY(_player->getY() + (rc.bottom - rc.top));
		}
	}
	else
	{
		if (_height2 >= TILESIZE * 7 - 24)
		{
			_height2 -= 2;
			_alpha = 1.f;
		}
		else
		{
			_height2 -= 0;
			_alpha = 0.5f;
		}
	}

	for (int i = 0; i < _em->getVBoss().size(); i++)
	{
		_hp = ((float)_em->getVBoss()[i]->getCurrentHP() / (float)_em->getVBoss() [i]->getMaxHP()) * 695;
	}

	changeScene();
}

void bossRoom1::render()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	TILEMANAGER->render();
	_em->render();
	_player->render();

	if (PRINTMANAGER->isDebug())
	DTDMANAGER->Rectangle(_room);

	//WCHAR str[128];
	//swprintf_s(str, L"summon : %d", _summonCount);
	//DTDMANAGER->printText(str, _player->getX(), _player->getY() - 50, 150, 20);

	if (_isStart)
	{
		IMAGEMANAGER->findDImage("bossHP_bot")->render(screen.left + 145, screen.bottom - 90, 0, 0, _hp, 45);
		IMAGEMANAGER->findDImage("bossHP_top")->render(screen.left + 120, screen.bottom - 100);
	}
	IMAGEMANAGER->findDImage("shadow")->render(_shadow.left, _shadow.top, 0.3f);
	IMAGEMANAGER->findDImage("shadow")->render(_shadow2.left, _shadow2.top, 0.3f);
	_entrance->render(TILESIZE * 18, _height, _alpha);
	_exit->render(TILESIZE * 18, _height2, _alpha2);
}

void bossRoom1::changeScene()
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
				SCENEMANAGER->changeScene("crypt1");
				_player->inDungeon();
				_player->setX(2380);
				_player->setY(520);
				_player->changeRune(_player->getDRune());
				_player->changeDRune(-_player->getDRune());
				TXTDATA->saveGame(_player);
				SOUNDMANAGER->stop("boss");
			}
		}
	}
}
