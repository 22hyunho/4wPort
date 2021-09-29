#include "stdafx.h"
#include "FoodMenu.h"
#include "Player.h"

HRESULT FoodMenu::init(Player* player)
{
	Menu::init(player);
	_screen = CAMERAMANAGER->getScreen();

	IMAGEMANAGER->addDImage("egg", L"img/food/food_egg.png", 83, 65);
	IMAGEMANAGER->addDImage("bread", L"img/food/food_bread.png", 80, 71);
	IMAGEMANAGER->addDImage("oatmeal", L"img/food/food_oatmeal.png", 80, 51);
	IMAGEMANAGER->addDImage("cabbagesoup", L"img/food/food_cabbagesoup.png", 80, 61);
	IMAGEMANAGER->addDImage("rabbitstew", L"img/food/food_rabbitstew.png", 80, 66);
	IMAGEMANAGER->addDImage("cookedbeans", L"img/food/food_cookedbeans.png", 80, 43);
	IMAGEMANAGER->addDImage("fishsoup", L"img/food/food_fishsoup.png", 80, 46);
	IMAGEMANAGER->addDImage("honeyboar", L"img/food/food_honeyboar.png", 80, 78);
	_selected = IMAGEMANAGER->addDImage("selected", L"img/ui/food_selected.png", 107, 25);
	_rune = IMAGEMANAGER->addDImage("rune_ui", L"img/ui/rune_ui.png", 54, 65);

	_back = IMAGEMANAGER->addDImage("background", L"img/ui/black.png", WINSIZEX, WINSIZEY);
	_border[0] = IMAGEMANAGER->addDImage("border1", L"img/ui/black.png", 550, 600);
	_border[1] = IMAGEMANAGER->addDImage("border2", L"img/ui/black.png", 400, 600);

	_choice[1] = RectMake(_screen.left + 225, _screen.top + 150, 149, 92);
	_choice[2] = RectMake(_screen.left + 40, _screen.top + 280, 149, 92);
	_choice[3] = RectMake(_screen.left + 225, _screen.top + 280, 149, 92);
	_choice[4] = RectMake(_screen.left + 405, _screen.top + 280, 149, 92);
	_choice[5] = RectMake(_screen.left + 120, _screen.top + 410, 149, 92);
	_choice[6] = RectMake(_screen.left + 340, _screen.top + 410, 149, 92);
	_choice[7] = RectMake(_screen.left + 120, _screen.top + 540, 149, 92);
	_choice[8] = RectMake(_screen.left + 340, _screen.top + 540, 149, 92);

	for (int i = 0; i < 8; i++)
	{
		_foodBack[i] = IMAGEMANAGER->addFrameDImage("foodBack1", L"img/ui/recipe_background.png", 447, 92, 3, 1);
	}
	_currentFood = _player->getFood();

	return S_OK;
}

void FoodMenu::release()
{
}

void FoodMenu::update()
{
	for (int i = 1; i < 9; i++)
	{
		if (PtInRect(&_choice[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				switch (i)
				{
				case FOOD_EGG:
					if (!_buy[FOOD_EGG] && _player->getRune() >= 6)
					{
						_player->changeRune(-6);
						_buy[FOOD_EGG] = true;
					}
					else if (_buy[FOOD_EGG])
					{
						_currentFood = FOOD_EGG;
						_player->setFood(FOOD_EGG);
					}
					
					break;

				case FOOD_BREAD:
					if (!_buy[FOOD_BREAD] && _player->getRune() >= 15)
					{
						_player->changeRune(-15);
						_buy[FOOD_BREAD] = true;
					}
					else if (_buy[FOOD_BREAD])
					{
						_currentFood = FOOD_BREAD;
						_player->setFood(FOOD_BREAD);
					}

					break;
					
				case FOOD_OATMEAL :
					if (!_buy[FOOD_OATMEAL] && _player->getRune() >= 15)
					{
						_player->changeRune(-15);
						_buy[FOOD_OATMEAL] = true;
					}
					else if (_buy[FOOD_OATMEAL])
					{
						_currentFood = FOOD_OATMEAL;
						_player->setFood(FOOD_OATMEAL);
					}
					
					break;

				case FOOD_CABBAGESOUP :
					if (!_buy[FOOD_CABBAGESOUP] && _player->getRune() >= 15)
					{
						_player->changeRune(-15);
						_buy[FOOD_CABBAGESOUP] = true;
					}
					else if (_buy[FOOD_CABBAGESOUP])
					{
						_currentFood = FOOD_CABBAGESOUP;
						_player->setFood(FOOD_CABBAGESOUP);
					}

					break;

				case FOOD_RABBITSTEW :
					if (!_buy[FOOD_RABBITSTEW] && _player->getRune() >= 35)
					{
						_player->changeRune(-35);
						_buy[FOOD_RABBITSTEW] = true;
					}
					else if (_buy[FOOD_RABBITSTEW])
					{
						_currentFood = FOOD_RABBITSTEW;
						_player->setFood(FOOD_RABBITSTEW);
					}

					break;

				case FOOD_COOKEDBEANS :
					if (!_buy[FOOD_COOKEDBEANS] && _player->getRune() >= 35)
					{
						_player->changeRune(-35);
						_buy[FOOD_COOKEDBEANS] = true;
					}
					else if (_buy[FOOD_COOKEDBEANS])
					{
						_currentFood = FOOD_COOKEDBEANS;
						_player->setFood(FOOD_COOKEDBEANS);
					}

					break;

				case FOOD_FISHSOUP :
					if (!_buy[FOOD_FISHSOUP] && _player->getRune() >= 72)
					{
						_player->changeRune(-72);
						_buy[FOOD_FISHSOUP] = true;
					}
					else if (_buy[FOOD_FISHSOUP])
					{
						_currentFood = FOOD_FISHSOUP;
						_player->setFood(FOOD_FISHSOUP);
					}

					break;

				case FOOD_HONEYBOAR :
					if (!_buy[FOOD_HONEYBOAR] && _player->getRune() >= 72)
					{
						_player->changeRune(-72);
						_buy[FOOD_HONEYBOAR] = true;
					}
					else if (_buy[FOOD_HONEYBOAR])
					{
						_currentFood = FOOD_HONEYBOAR;
						_player->setFood(FOOD_HONEYBOAR);
					}

					break;
				}
		}
	}
	if (_buy)
	{
		switch (_currentFood)
		{
		case FOOD_EGG :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_EGG));
			break;

		case FOOD_BREAD :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_BREAD));
			break;

		case FOOD_OATMEAL :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_OATMEAL));
			break;

		case FOOD_CABBAGESOUP :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_CABBAGESOUP));
			break;

		case FOOD_RABBITSTEW :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_RABBITSTEW));
			break;

		case FOOD_COOKEDBEANS :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_COOKEDBEANS));
			break;

		case FOOD_FISHSOUP :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_FISHSOUP));
			break;

		case FOOD_HONEYBOAR :
			INVENTORY->clearFoodList();
			INVENTORY->addFood(FOODDEX->makeFood(FOOD_HONEYBOAR));
			break;
		}
	}
}

void FoodMenu::render()
{
	Menu::render();

	_border[0]->render(_screen.left + 20, _screen.top + 100, 0.7f);
	_border[1]->render(_screen.left + 580, _screen.top + 100, 0.7f);

	_foodBack[0]->frameRender(_screen.left + 225, _screen.top + 150, 0, 0);
	_foodBack[1]->frameRender(_screen.left + 40, _screen.top + 280, 0, 0);
	_foodBack[2]->frameRender(_screen.left + 225, _screen.top + 280, 0, 0);
	_foodBack[3]->frameRender(_screen.left + 405, _screen.top + 280, 0, 0);
	_foodBack[4]->frameRender(_screen.left + 120, _screen.top + 410, 0, 0);
	_foodBack[5]->frameRender(_screen.left + 340, _screen.top + 410, 0, 0);
	_foodBack[6]->frameRender(_screen.left + 120, _screen.top + 540, 0, 0);
	_foodBack[7]->frameRender(_screen.left + 340, _screen.top + 540, 0, 0);

	IMAGEMANAGER->findDImage("egg")->render(_screen.left + 258, _screen.top + 164);
	IMAGEMANAGER->findDImage("bread")->render(_screen.left + 75, _screen.top + 290);
	IMAGEMANAGER->findDImage("oatmeal")->render(_screen.left + 260, _screen.top + 305);
	IMAGEMANAGER->findDImage("cabbagesoup")->render(_screen.left + 440, _screen.top + 295);
	IMAGEMANAGER->findDImage("rabbitstew")->render(_screen.left + 153, _screen.top + 425);
	IMAGEMANAGER->findDImage("cookedbeans")->render(_screen.left + 373, _screen.top + 440);
	IMAGEMANAGER->findDImage("fishsoup")->render(_screen.left + 155, _screen.top + 568);
	IMAGEMANAGER->findDImage("honeyboar")->render(_screen.left + 373, _screen.top + 545);

	if (PRINTMANAGER->isDebug()) 
	{
		for (int i = 1; i < 9; i++)
			DTDMANAGER->Rectangle(_choice[i]);
	}

	for (int i = 1; i < 9; i++)
		if (PtInRect(&_choice[i], _ptMouse))
		{
			switch (i)
			{
			case 1 :
				eggInfo();
				break;
			case 2 :
				breadInfo();
				break;
			case 3 :
				oatmealInfo();
				break;
			case 4 :
				cabbagesoupInfo();
				break;
			case 5 :
				rabbitstewInfo();
				break;
			case 6 :
				cookedbeansInfo();
				break;
			case 7 :
				fishsoupInfo();
				break;
			case 8 :
				honeyboarInfo();
				break;
			}
		}

	if (_currentFood >= FOOD_EGG && _currentFood <= FOOD_HONEYBOAR)
	{
		switch (_currentFood)
		{
		case FOOD_EGG :
			_selected->render(_screen.left + 246, _screen.top + 235);
			break;
		case FOOD_BREAD :
			_selected->render(_screen.left + 61, _screen.top + 365);
			break;
		case FOOD_OATMEAL :
			_selected->render(_screen.left + 246, _screen.top + 365);
			break;
		case FOOD_CABBAGESOUP :
			_selected->render(_screen.left + 426, _screen.top + 365);
			break;
		case FOOD_RABBITSTEW :
			_selected->render(_screen.left + 141, _screen.top + 495);
			break;
		case FOOD_COOKEDBEANS :
			_selected->render(_screen.left + 361, _screen.top + 495);
			break;
		case FOOD_FISHSOUP :
			_selected->render(_screen.left + 141, _screen.top + 625);
			break;
		case FOOD_HONEYBOAR :
			_selected->render(_screen.left + 361, _screen.top + 625);
			break;
		}
	}
}

void FoodMenu::eggInfo()
{
	DTDMANAGER->printText(L"속을 채운 계란", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"속을 알차게 채운 계란입니다. \n코인 획득량을 증가시킵니다.", _screen.left + 850, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_EGG])
	{
		DTDMANAGER->printText(L"구     매 :   6", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::breadInfo()
{
	DTDMANAGER->printText(L"통밀 빵", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"통밀로 만든 빵입니다. \n체력을 증가시킵니다.", _screen.left + 870, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_BREAD])
	{
		DTDMANAGER->printText(L"구     매 :   15", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::oatmealInfo()
{
	DTDMANAGER->printText(L"밀 & 사과 오트밀", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"사과와 밀이 들어간 오트밀입니다. \n공격력을 증가시킵니다.", _screen.left + 840, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_OATMEAL])
	{
		DTDMANAGER->printText(L"구     매 :   15", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::cabbagesoupInfo()
{
	DTDMANAGER->printText(L"당근 수프", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"당근으로 만든 수프입니다. \n공격속도를 증가시킵니다.", _screen.left + 860, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_CABBAGESOUP])
	{
		DTDMANAGER->printText(L"구     매 :   15", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::rabbitstewInfo()
{
	DTDMANAGER->printText(L"토끼고기 스튜", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"토끼고기가 들어간 스튜입니다. \n공격력을 증가시키며 코인 \n획득량을 증가시킵니다",
		_screen.left + 850, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_RABBITSTEW])
	{
		DTDMANAGER->printText(L"구     매 :   35", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::cookedbeansInfo()
{
	DTDMANAGER->printText(L"구운 보리 & 콩", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"보리와 콩을 구운 요리입니다. \n체력과 공격속도를 증가시킵니다.", _screen.left + 845, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_COOKEDBEANS])
	{
		DTDMANAGER->printText(L"구     매 :   35", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::fishsoupInfo()
{
	DTDMANAGER->printText(L"생선 & 베이컨차우더", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"생선과 베이컨이 들어간 차우더\n입니다. 공격력과 공격속도, \n코인 획득량을 증가시킵니다.", _screen.left + 845, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_FISHSOUP])
	{
		DTDMANAGER->printText(L"구     매 :   72", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}

void FoodMenu::honeyboarInfo()
{
	DTDMANAGER->printText(L"구운 멧돼지 다리", _screen.left + 785, _screen.top + 180, 300, 40, 30);
	DTDMANAGER->printText(L"꿀을 곁들인 멧돼지 다리 요리\n입니다. 체력과 공격속도, \n코인 획득량을 증가시킵니다.", _screen.left + 845, _screen.top + 350, 500, 200, 25);
	if (!_buy[FOOD_HONEYBOAR])
	{
		DTDMANAGER->printText(L"구     매 :   72", _screen.left + 850, _screen.top + 700, 500, 200, 30);
		_rune->render(_screen.left + 810, _screen.top + 590);
	}
}
