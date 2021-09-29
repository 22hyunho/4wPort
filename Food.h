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
	wstring			_name;		//ǥ�ÿ� �̸�
	wstring			_info;		//������ �Ұ�
	ARTIFACTLIST	_type;		//������ Ÿ��
	float			_x, _y;		//�ѷ����� ��ǥ��
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

