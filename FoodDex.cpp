#include "stdafx.h"
#include "FoodDex.h"
#include "Egg.h"
#include "MealBread.h"
#include "Oatmeal.h"
#include "CabbageSoup.h"
#include "RabbitStew.h"
#include "CookedBeans.h"
#include "FishSoup.h"
#include "HoneyBoar.h"

HRESULT FoodDex::init()
{
	registerFood(FOOD_EGG, new Egg);
	registerFood(FOOD_BREAD, new MealBread);
	registerFood(FOOD_OATMEAL, new Oatmeal);
	registerFood(FOOD_CABBAGESOUP, new CabbageSoup);
	registerFood(FOOD_RABBITSTEW, new RabbitStew);
	registerFood(FOOD_COOKEDBEANS, new CookedBeans);
	registerFood(FOOD_FISHSOUP, new FishSoup);
	registerFood(FOOD_HONEYBOAR, new HoneyBoar);

	return S_OK;
}

void FoodDex::release()
{
}

void FoodDex::update()
{
}

void FoodDex::render()
{
}

Food * FoodDex::registerFood(int num, Food * food)
{
	if (!food)	return nullptr;

	_mFood.insert(make_pair(num, food));

	return food;
}

Food * FoodDex::makeFood(int num)
{
	_miFood = _mFood.find(num);
	if (_miFood == _mFood.end()) return nullptr;
	else						 return _miFood->second;
}
