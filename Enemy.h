#pragma once
#include "EnemyArrow.h"
class Player;
class Pattern;

enum ENEMYLIST
{
	EM_BAT,
	EM_WOLF,
	EM_PLANT,
	EM_PLANTPOT,
	EM_MINION,
	EM_SPIDER,
	EM_ORC,
	EM_ORCWARRIOR,
	EM_SPIDERQUEEN,
	EM_SKELETON,
	EM_ARMORSKELETON,
	EM_GULD
};

enum ENEMYSTATE
{
	ES_IDLE,
	ES_MOVE,
	ES_ATTACK,
	ES_HURT,
	ES_DIE,
	ES_COOLDOWN
};

enum ENEMYPATTERN
{
	PT_DEFAULT,
	PT_PATHFIND,
	PT_ATTACK,
	PT_ENDPATTERN
};

enum ENEMYTYPE
{
	TY_MELEE,
	TY_RANGE,
	TY_SPECIAL
};

class Enemy
{
protected :
	//몸체
	RECT _rc;
	float _x, _y, _z;
	float _endX, _endY;
	float _angle;
	float _kAngle;
	float _knockBack;
	float _gravity;
	int _direct;

	//스텟
	int _currentHP, _maxHP;
	int _damage;
	int _speed;

	//이미지
	dImage* _img;
	int _frameX, _frameY;
	int _tuningX, _tuningY;
	float _count;
	float _individualFrame;

	//감지범위
	RECT _detection;
	RECT _attackBox;
	bool _trace;
	int _traceCount;

	//패턴
	ENEMYSTATE _state;
	Pattern* _pattern[PT_ENDPATTERN];
	ENEMYPATTERN _currentPattern;
	ENEMYTYPE _type;
	Player* _player;
	bool _death;

	int _hurtCount;
	int _dieCount;
	int _attackCount;
	int _coolDownCount;
	bool _coolDown;

public :
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init(float x, float y, Player* player);
	virtual void release() = 0;
	virtual void update();
	virtual void render() = 0;
	virtual void controlFrame() = 0;

	virtual void move();
	virtual void knockBack();
	virtual void knockBack(float angle);

	virtual void changePattern(ENEMYPATTERN pattern);
	virtual void changeState(ENEMYSTATE state) = 0;

	virtual void changeHP(int damage);
	//=====================접근자&설정자=====================
	RECT getRect() { return _rc; }
	void setRect(float x, float y, int width, int height) { _rc = RectMakeCenter(x, y, width, height); }
	RECT getDetection() { return _detection; }
	RECT getAttackBox() { return _attackBox; }

	float getX() { return _x; }
	void setX(float x) { _x = x; }

	float getY() { return _y; }
	void setY(float y) { _y = y; }

	float getZ() { return _z; }

	void setFrameX(int frameX) { _frameX = frameX; }

	float getEndX() { return _endX; }
	void setEndX(float x) { _endX = x; }
	float getEndY() { return _endY; }
	void setEndY(float y) { _endY = y; }

	int getCurrentHP() { return _currentHP; }
	
	int getMaxHP() { return _maxHP; }
	void setMaxHP(int hp) { _maxHP = hp; }

	int getSpeed() { return _speed; }
	void setSpeed(int speed) { _speed = speed; }

	bool getDeath() { return _death; }
	void setDeath(bool death) { _death = death; }

	bool getCoolDown() { return _coolDown; }
	void setCoolDown(bool coolDown) { _coolDown = coolDown; }

	bool getTrace() { return _trace; }

	Pattern* getPattern() { return _pattern[1]; }

	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	ENEMYTYPE getType() { return _type; }

	dImage* getImage() { return _img; }
};

