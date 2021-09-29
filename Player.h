#pragma once
#include "Character.h"
#include "PlayerSetting.h"
#include "arrowManager.h"
#include "trapManager.h"

class Player
{
private :
	//몸체
	Character* _character;
	float _x, _y, _z;
	int _direct;
	int _index;
	float _angle;
	RECT _rc;
	bool _town;
	bool _death;

	//스텟
	int _currentHP, _maxHP, _baseHP;
	int _armor, _stone;
	int _atkSpeed, _baseAts;
	int _damage, _baseDamage;
	int _speed, _baseSpd;

	//소지품 & 장착아이템
	int _gold;
	int _rune;
	int _dungeonRune;
	int _currentTrap;
	int _currentFood;

	//무기
	arrowManager* _arrow;
	trapManager* _trap;
	int _bearLevel;
	int _slowLevel;

	bool _hunterCooltime;
	bool _trapCooltime;
	int _ctCount;
	int _boltCount;
	int _trapCount;

	//아티팩트 능력
	bool _bread;
	bool _drain;
	bool _leaf;

	//음식능력
	bool _coinChance;

	//기타
	int _dodgeCount;
	bool _dodge;
	int _effectCount;

	int _test;

public :
	Player() {};
	~Player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void plusHP(int value);
	void minusHP(int damage);
	void changeCharacter(Character* character);

	void controlKey();
	void move();
	void downStair();
	void moveDodge();

	//=====================접근자&설정자=====================
	Character* getCharacter() { return _character; }

	trapManager* getTrapManager() { return _trap; }

	RECT getRect() { return _rc; }
	void setRect(float x, float y, int width, int height) { _rc = RectMakeCenter(x, y, width, height); }

	void inTown() { _town = true; }
	void inDungeon() { _town = false; }
	bool getTown() { return _town; }

	bool getDeath() { return _death; }
	void setDeath(bool death) { _death = death; }

	bool getTrapCool() { return _trapCooltime; }

	int getTrapTime() { return _trapCount; }

	float getX() { return _x; }
	void setX(float x) { _x = x; }

	float getY() { return _y; }
	void setY(float y) { _y = y; }

	float getZ() { return _z; }

	int getIndex() { return _index; }

	int getGold() { return _gold; }
	void changeGold(int gold) { _gold += gold; }
	void setGold(int gold) { _gold = gold; }

	int getRune() { return _rune; }
	void changeRune(int rune) { _rune += rune; }
	void setRune(int rune) { _rune = rune; }

	int getDRune() { return _dungeonRune; }
	void changeDRune(int rune) { _dungeonRune += rune; }
	void setDRune(int rune) { _dungeonRune = rune; }

	int getCurrentHP() { return _currentHP; }
	void setCurrentHP(int hp) { _currentHP = hp; }

	int getMaxHP() { return _maxHP; }
	void setMaxHP(int hp) { _maxHP = hp; }
	void resetHP() { _maxHP = _baseHP; _currentHP = _baseHP; }

	int getChance() { return _coinChance; }
	void setChance(bool chance) { _coinChance = chance; }

	int getArmor() { return _armor; }
	void setArmor(int armor) { _armor = armor; }

	int getStone() { return _stone; }
	void setStone(int stone) { _stone = stone; }

	int getDamage() { return _damage; }
	void resetDamage() { _damage = _baseDamage; }
	void changeDamage(int damage) { _damage += damage; }

	void resetSpeed() { _speed = 4; }
	void changeSpeed(int speed) { _speed += speed; }

	int getDirect() { return _direct; }

	void resetAtkSpd() { _atkSpeed = _baseAts; }
	void changeAtkSpd(int atkSpd) { _atkSpeed -= atkSpd; }

	int getTrap() { return _currentTrap; }
	void setTrap(int trap) { _currentTrap = trap; }

	int getFood() { return _currentFood; }
	void setFood(int food) { _currentFood = food; }

	int getBearLevel() { return _bearLevel; }
	void plusBearLevel() { _bearLevel += 1; }
	void setBearLevel(int level) { _bearLevel = level; }
	
	int getSlowLevel() { return _slowLevel; }
	void plusSlowLevel() { _slowLevel += 1; }
	void setSlowLevel(int level) { _slowLevel = level; }

	bool getBread() { return _bread; }
	void setBread(bool bread) { _bread = bread; }

	bool getDrain() { return _drain; }
	void setDrain(bool drain) { _drain = drain; }

	bool getLeaf() { return _leaf; }
	void setLeaf(bool leaf) { _leaf = leaf; }

	int getBaseDmg() { return _baseDamage; }
	void setBaseDmg(int damage) { _baseDamage = damage; }
	void resetBaseDmg() { _baseDamage = _character->getDamage(); }

	int getBaseAts() { return _baseAts; }
	void setBaseAts(int atkSpeed) { _baseAts = atkSpeed; }
	void resetBaseAts() { _baseAts = 40; }

	int getBaseHP() { return _baseHP; }
	void setBaseHP(int hp) { _baseHP = hp; }
	void resetBaseHP() { _baseHP = _character->getHP(); }
};

