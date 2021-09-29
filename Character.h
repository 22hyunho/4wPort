#pragma once
enum CONTROLCHARACTER
{
	CH_HUNTER,
	CH_XBOW
};

enum STATE
{
	ST_IDLE,
	ST_RUN,
	ST_AIMING,
	ST_SHOOT,
	ST_MOVINGSHOOT,
	ST_DODGE,
	ST_DEPLOY,
	ST_HURT,
	ST_DIE
};

class Character
{
protected :
	//몸체
	RECT _rc;
	RECT _interactRc;
	float _x, _y, _z;
	int _direct;
	int _index;
	STATE _state;
	bool _dodge;
	bool _invincible;
	int _invCount;
	int _dieCount;

	//스탯
	int _hp;
	int _damage;

	//이미지
	dImage* _img;
	dImage* _bow;
	dImage* _aim;
	int _frameX, _frameY;
	float _count;
	float _tuningX, _tuningY, _tuningFrame;
	float _alpha;
	int _hurtCount;

	//음식 적용 (캐릭터에)
	bool food[8];

public :
	Character() {};
	~Character() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update() = 0;
	virtual void render(float x, float y, float angle) = 0;
	virtual void render();
	virtual void controlFrame();

	virtual void changeState(STATE state);

	//=====================접근자&설정자=====================
	RECT getRect() { return _rc; }
	RECT getInteractRect() { return _interactRc; }

	dImage* getImage() { return _img; }

	float getX() { return _x; }

	float getY() { return _y; }

	int getDirect() { return _direct; }
	void setDirect(int direct) { _direct = direct; }

	int getIndex() { return _index; }

	int getHP() { return _hp; }
	void setHP(int hp) { _hp = hp; }

	int getDamage() { return _damage; }
	void setDamage(int damage) { _damage = damage; }

	int getFrameX() { return _frameX; }

	int getFrameY() { return _frameY; }
	void setFrameY(int frameY) { _frameY = frameY; }

	STATE getState() { return _state; }

	bool getDodge() { return _dodge; }

	int getInvCount() { return _invCount; }

	bool getInvincible() { return _invincible; }
	void setInvincible(bool inv) { _invincible = inv; }
};

