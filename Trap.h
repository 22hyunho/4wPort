#pragma once
enum TRAPTYPE
{
	BEARTRAP,
	SLOWTRAP
};
class Trap
{
protected :
	dImage* _img;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _fireX, _fireY;
	float _range;
	float _count;
	int _type;
	int _level;
	int _damage;
	int _slow;
	int _index;
	int _frameX, _frameY;
	int _offCount;
	bool _off;
	bool _deploy;
	bool _unfold;

public :
	Trap() {};
	~Trap() {};

	virtual HRESULT init(float x, float y, POINT point, int level);
	virtual void release() = 0;
	virtual void update();
	virtual void render() = 0;

	//=====================접근자&설정자=====================

	RECT getRect() { return _rc; }

	int getType() { return _type; }
	
	int getLevel() { return _level; }

	int getDamage() { return _damage; }

	bool getDeploy() { return _deploy; }
	void setDeploy(bool deploy) { _deploy = deploy; }

	bool getUnfold() { return _unfold; }
	void setUnfold(bool unfold) { _unfold = unfold; }

	bool getOff() { return _off; }
	void setOff(bool off) { _off = off; }
};

