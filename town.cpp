#include "stdafx.h"
#include "town.h"
#include "Player.h"
#include "Ellis.h"
#include "Jessica.h"
#include "NPC_blacksmith.h"
#include "NPC_cook.h"
#include "NPC_taylor.h"
#include "NPC_skill.h"

HRESULT town::init(Player * player)
{
	Scene::init(player);
	IMAGEMANAGER->addDImage("ellisBack", L"img/ui/back_ellis.png", 1248, 702);
	IMAGEMANAGER->addDImage("jessicaBack", L"img/ui/back_jessica.png", 1248, 702);
	IMAGEMANAGER->addDImage("black", L"img/ui/black.png", 600, 300);
	IMAGEMANAGER->addFrameDImage("fire", L"img/object/fire1.png", 351, 45, 13, 1);
	IMAGEMANAGER->addDImage("select", L"img/ui/trap_select.png", 110, 50);
	IMAGEMANAGER->addDImage("back", L"img/ui/trap_background.png", 169, 127);

	_currentFood = IMAGEMANAGER->addDImage("egg", L"img/food/food_egg.png", 83, 65);
	IMAGEMANAGER->addDImage("bread", L"img/food/food_bread.png", 80, 71);
	IMAGEMANAGER->addDImage("oatmeal", L"img/food/food_oatmeal.png", 80, 51);
	IMAGEMANAGER->addDImage("cabbagesoup", L"img/food/food_cabbagesoup.png", 80, 61);
	IMAGEMANAGER->addDImage("rabbitstew", L"img/food/food_rabbitstew.png", 80, 66);
	IMAGEMANAGER->addDImage("cookedbeans", L"img/food/food_cookedbeans.png", 80, 43);
	IMAGEMANAGER->addDImage("fishsoup", L"img/food/food_fishsoup.png", 80, 46);
	IMAGEMANAGER->addDImage("honeyboar", L"img/food/food_honeyboar.png", 80, 78);

	_currentTrap = IMAGEMANAGER->addDImage("bear", L"img/trap/bearTrap_info.png", 78, 57);
	PLAYERUI->setTrapImage(_currentTrap);
	IMAGEMANAGER->addDImage("slow", L"img/trap/slowTrap_info.png", 80, 60);
	_tX = 430;
	_tY = 680;
	_tUp = true;
	_fX = 775;
	_fY = 570;
	_fUp = true;

	_characterSelect = false;
	_player->setX(600);
	_player->setY(600);
	_player->inTown();
	_frame = 0;
	_fireX = 0;

	TILEMANAGER->load("town.map", 55, 30);
	CAMERAMANAGER->setBackScreenSize(TILESIZE * 55, TILESIZE * 30);

	_character[CH_HUNTER] = new Ellis;
	_character[CH_HUNTER]->init();
	_character[CH_XBOW] = new Jessica;
	_character[CH_XBOW]->init();

	_NPC[NPC_BLACKSMITH] = new NPC_blacksmith;
	_NPC[NPC_BLACKSMITH]->init(405, 745);
	_NPC[NPC_COOK] = new NPC_cook;
	_NPC[NPC_COOK]->init(840, 745);
	_NPC[NPC_TAYLOR] = new NPC_taylor;
	_NPC[NPC_TAYLOR]->init(555, 645);
	_NPC[NPC_SKILL] = new NPC_skill;
	_NPC[NPC_SKILL]->init(1105, 815);

	COLLISIONMANAGER->init(this);
	SOUNDMANAGER->play("town");

	TXTDATA->loadGame(_player);
	return S_OK;
}

void town::release()
{
}

void town::update()
{
	PLAYERUI->setTrapImage(_currentTrap);
	UIMANAGER->update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_F10)) TXTDATA->saveGame(_player);
	if (KEYMANAGER->isOnceKeyDown(VK_F11)) TXTDATA->loadGame(_player);

	uiUpdate();
	characterChange();
	equipChange();
	changeScene();
	changeImage();
}

void town::render()
{
	TILEMANAGER->render();
	for (int i = 0; i < 4; i++)
	{
		_NPC[i]->render();
	}

	switch (_player->getIndex())
	{
	case CH_HUNTER :
		_character[CH_XBOW]->render();
		break;

	case CH_XBOW :
		_character[CH_HUNTER]->render();
		break;
	}

	_player->render();

	IMAGEMANAGER->findDImage("fire")->frameRender(653, 795, _fireX, 0);

	RECT rc;
	for (int i = 0; i < 4; i++)
	{
		if (IntersectRect(&rc, &_player->getRect(), &_NPC[i]->getInteractRect()))
		{
			_keyE->render(_NPC[i]->getX() - 24, _NPC[i]->getY() - TILESIZE * 2);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&rc, &_player->getRect(), &_character[i]->getInteractRect()) &&
			_player->getIndex() != _character[i]->getIndex())
		{
			_keyE->render(_character[i]->getX() - 24, _character[i]->getY() - TILESIZE * 2);
		}
	}

	_currentTrap->render(_tX, _tY, 0.5f);
	if (_player->getFood() >= FOOD_EGG && _player->getFood() <= FOOD_HONEYBOAR) _currentFood->render(_fX, _fY, 0.5f);

	IMAGEMANAGER->findDImage("black")->render(CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top, 0, 0, 1000, 800, 0.2f);
	if (UIMANAGER->getOpen()) UIMANAGER->render();
	changeRender();
}

void town::characterChange()
{
	RECT rc;
	for (int i = 0; i < 2; i++)
		if (IntersectRect(&rc, &_player->getRect(), &_character[i]->getInteractRect()))
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
				_characterSelect = true;
		}

	for (int i = 0; i < 2; i++)
		if (PtInRect(&_select[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch (i)
				{
				case 0:
					if (_player->getIndex() == CH_HUNTER) _player->changeCharacter(_character[CH_XBOW]);
					else if (_player->getIndex() == CH_XBOW) _player->changeCharacter(_character[CH_HUNTER]);
					_characterSelect = false;
					break;
				case 1:
					_characterSelect = false;
					break;
				}
			}
		}
}

void town::equipChange()
{
	RECT rc;
	for (int i = 0; i < 4; i++)
		if (IntersectRect(&rc, &_player->getRect(), &_NPC[i]->getInteractRect()))
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				switch (i)
				{
				case NPC_BLACKSMITH :
					UIMANAGER->setOpen(!UIMANAGER->getOpen());
					if (UIMANAGER->getOpen()) UIMANAGER->changeMenu("trapMenu");
					break;

				case NPC_COOK :
					UIMANAGER->setOpen(!UIMANAGER->getOpen());
					if (UIMANAGER->getOpen()) UIMANAGER->changeMenu("foodMenu");
					else UIMANAGER->changeMenu("NULL");
					break;
				}
			}
		}
}

void town::changeRender()
{
	if (_characterSelect)
	{
		if (_player->getIndex() == CH_HUNTER)
		{
			IMAGEMANAGER->findDImage("jessicaBack")->render(CAMERAMANAGER->getScreen().left, CAMERAMANAGER->getScreen().top + 50);
			IMAGEMANAGER->findDImage("black")->render(CAMERAMANAGER->getScreen().left + 215, CAMERAMANAGER->getScreen().top + 300, 0.7f);
			DTDMANAGER->printText(L"캐릭터를 석궁경비대 제시카로 교체 하시겠습니까?",
				CAMERAMANAGER->getScreen().left + 515,
				CAMERAMANAGER->getScreen().top + 400, 500, 50, 25);
		}
		else if (_player->getIndex() == CH_XBOW)
		{
			IMAGEMANAGER->findDImage("ellisBack")->render(CAMERAMANAGER->getScreen().left + 120, CAMERAMANAGER->getScreen().top - 70);
			IMAGEMANAGER->findDImage("black")->render(CAMERAMANAGER->getScreen().left + 215, CAMERAMANAGER->getScreen().top + 300, 0.7f);
			DTDMANAGER->printText(L"캐릭터를 사냥꾼 엘리스로 교체 하시겠습니까?",
				CAMERAMANAGER->getScreen().left + 515,
				CAMERAMANAGER->getScreen().top + 400, 500, 50, 25);
		}

		_select[0] = RectMake(CAMERAMANAGER->getScreen().left + 305, CAMERAMANAGER->getScreen().top + 480, 100, 80);
		_select[1] = RectMake(CAMERAMANAGER->getScreen().left + 605, CAMERAMANAGER->getScreen().top + 480, 100, 80);
		for (int i = 0; i < 2; i++)
			if (PtInRect(&_select[i], _ptMouse))
				DTDMANAGER->Rectangle(_select[i]);
		DTDMANAGER->printText(L"예", CAMERAMANAGER->getScreen().left + 370, CAMERAMANAGER->getScreen().top + 520, 50, 30, 25);
		DTDMANAGER->printText(L"아니오", CAMERAMANAGER->getScreen().left + 660, CAMERAMANAGER->getScreen().top + 520, 75, 30, 25);
	}
}

void town::changeScene()
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
				SCENEMANAGER->changeScene("forest1");
				_player->inDungeon();
				_player->setX(480);
				_player->setY(360);
				SOUNDMANAGER->stop("town");
			}
		}
	}
}

void town::changeImage()
{
	if (_tY > 710)			_tUp = true;
	else if (_tY < 670)		_tUp = false;
	if (_tUp)				_tY -= 0.5f;
	else					_tY += 0.5f;
	if (_fY > 600)			_fUp = true;
	else if (_fY < 560)		_fUp = false;
	if (_fUp)				_fY -= 0.5f;
	else					_fY += 0.5f;

	if (_player->getTrap() == TRAP_BEAR)		_currentTrap = IMAGEMANAGER->findDImage("bear");
	else if (_player->getTrap() == TRAP_SLOW)	_currentTrap = IMAGEMANAGER->findDImage("slow");

	switch (_player->getFood())
	{
	case FOOD_EGG:
		_currentFood = IMAGEMANAGER->findDImage("egg");
		break;

	case FOOD_BREAD:
		_currentFood = IMAGEMANAGER->findDImage("bread");
		break;

	case FOOD_OATMEAL:
		_currentFood = IMAGEMANAGER->findDImage("oatmeal");
		break;

	case FOOD_CABBAGESOUP:
		_currentFood = IMAGEMANAGER->findDImage("cabbagesoup");
		break;

	case FOOD_RABBITSTEW:
		_currentFood = IMAGEMANAGER->findDImage("rabbitstew");
		break;

	case FOOD_COOKEDBEANS:
		_currentFood = IMAGEMANAGER->findDImage("cookedbeans");
		break;

	case FOOD_FISHSOUP:
		_currentFood = IMAGEMANAGER->findDImage("fishsoup");
		break;

	case FOOD_HONEYBOAR:
		_currentFood = IMAGEMANAGER->findDImage("honeyboar");
		break;
	}
}

void town::uiUpdate()
{
	if (!UIMANAGER->getOpen())
	{
		for (int i = 0; i < 4; i++)
			COLLISIONMANAGER->playerWithNPC(_NPC[i]);
		for (int i = 0; i < 2; i++)
			COLLISIONMANAGER->playerWithCharacter(_character[i]);
		if (!_characterSelect && CAMERAMANAGER->getFade() >= 0)_player->update();
		TILEMANAGER->update();

		CAMERAMANAGER->updateScreen(_player->getX(), _player->getY());

		_frame += TIMEMANAGER->getElapsedTime();
		if (_frame > 0.07f)
		{
			if (_fireX >= 12)
				_fireX = 0;
			else _fireX++;

			_frame = 0;
		}
	}
}
