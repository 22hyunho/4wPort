#pragma once
enum ARROWLIST
{
	ARROW_HUNTER,
	ARROW_XBOW
};

class Arrow
{
protected :
	dImage* _img;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _fireX, _fireY;
	float _range;
	int _count;
	int _index;
	bool _off;

public :
	Arrow() {};
	~Arrow() {};
	virtual HRESULT init(float x, float y, float angle) = 0;
	virtual void release() = 0;
	virtual void update();
	virtual void render() = 0;

	virtual void move() = 0;

	//=====================접근자&설정자=====================
	bool getOff() { return _off; }

	void setOff(bool onAndOff) { _off = onAndOff; }

	RECT getRect() { return _rc; }
};

