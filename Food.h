#pragma once

class Player;

enum FOODLIST
{
	FOOD_EGG = 1,
	FOOD_BREAD,
	FOOD_OATMEAL,
	FOOD_CABBAGESOUP,
	FOOD_RABBITSTEW,
	FOOD_COOKEDBEANS,
	FOOD_FISHSOUP,
	FOOD_HONEYBOAR
};
class Food
{
protected :
	wstring			_name;		//표시용 이름
	wstring			_info;		//아이템 소개
	ARTIFACTLIST	_type;		//아이템 타입
	float			_x, _y;		//뿌려지는 좌표값
	int				_count;
	bool			_off;

public :
	Food() {};
	~Food() {};

	virtual HRESULT init(Player* player) = 0;
	virtual void release();
	virtual void update();
	virtual void render();
};

