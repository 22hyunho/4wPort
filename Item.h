#pragma once
enum ITEMTYPE
{
	TY_GOLD,
	TY_RUNE,
	TY_MEAT
};
class Item
{
protected :
	RECT _rc;
	dImage* _img;
	float _x, _y;
	float _angle;
	float _speed;
	int _value;
	bool _off;

	ITEMTYPE _type;

public :
	Item() {};
	~Item() {};

	virtual HRESULT init(float x, float y, float angle, int value);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//=====================접근자&설정자=====================
	RECT getRect() { return _rc; }

	ITEMTYPE getType() { return _type; }

	int getValue() { return _value; }

	bool getOff() { return _off; }
	void setOff(bool off) { _off = off; }
};