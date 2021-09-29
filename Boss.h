#pragma once
#include "EnemyArrow.h"
class Player;

enum BOSSTYPE
{
	B_BEHOLDER,
	B_HALFELF,
	B_FINAL
};

enum BOSSSTATE
{
	BS_IDLE,
	BS_MOVE,
	BS_ATTACK,
	BS_HURT,
	BS_DYING,
	BS_DEAD,
	BS_ATTACK2,
	BS_FLY,
	BS_CHARGE,
	BS_TRANSFORM,
};
class Boss
{
protected :
	RECT _rc;
	RECT _detection;
	Player* _player;
	float _x, _y, _z;
	int _direct;
	float _angle;

	//스텟
	int _currentHP, _maxHP;
	int _damage;
	float _speed;

	//이미지
	float _count;
	int _icount;
	int _frameX, _frameY;
	int _individualFrame;

	BOSSSTATE _state;

	int _hurtCount;
	int _dieCount;

	bool _invincible;
	bool _death;
	bool _start;

	SphereSpell* _spell;
public :
	Boss() {};
	~Boss() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void changeState(BOSSSTATE state) = 0;

	virtual void changeHP(int damage);

	//=====================접근자&설정자=====================

	RECT getRect() { return _rc; }

	float getX() { return _x; }
	
	float getY() { return _y; }

	void setFrameX(int frameX) { _frameX = frameX; }

	int getCurrentHP() { return _currentHP; }

	int getMaxHP() { return _maxHP; }

	bool getDeath() { return _death; }
	void setDeath(bool death) { _death = death; }

	bool getInv() { return _invincible; }

	BOSSSTATE getState() { return _state; }

	SphereSpell* getSpell() { return _spell; }
};

