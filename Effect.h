#pragma once

enum EFFECTTYPE
{
	EF_ATTACK,
	EF_NONATTACK
};

class Effect
{
protected :
	RECT _rc;
	dImage* _img;
	EFFECTTYPE _type;
	float _x, _y;
	float _fireX, _fireY;
	float _angle;
	float _speed;
	float _range;
	float _count;
	int _offCount;
	int _frameX, _frameY;
	int _width, _height;
	int _damage;

	bool _off;
	bool _reverse;
public :
	Effect() {};
	~Effect() {};

	virtual HRESULT init(float x, float y, int width, int height);
	virtual HRESULT init(int frameX, int frameY, float x, float y);
	virtual HRESULT init(float x, float y, float angle);
	virtual HRESULT init(float x, float y, bool reverse);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	RECT getRect() { return _rc; }

	EFFECTTYPE getType() { return _type; }

	float getX() { return _x; }
	float getY() { return _y; }

	bool getOff() { return _off; }

	int getDamage() { return _damage; }
};

