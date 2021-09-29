#pragma once
#include "singletonBase.h"
#include "tileInfo.h"
#include <vector>

class Player;
class Scene;
class Character;
class Arrow;
class PlasmaBall;
class PlasmaCannon;
class SphereSpell;
class Trap;
class NPC;
class enemyManager;
class Enemy;
class Item;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Scene* _scene;
	Player* _player;
	enemyManager* _em;
	tagTile* _allTile;		//타일 목록
	vector<Item*>* _allItem;		//아이템 목록

	float _eX, _eY;
	int _kill;
	//충돌하는 객체들 파악하기
	//플레이어랑 에너미
	//플레이어랑 아이템

public:
	collisionManager() {};
	~collisionManager() {};

	HRESULT init(Scene* scene);
	HRESULT init(Player* player);
	HRESULT init(enemyManager* enemy);
	void release();

	void collisionPlayer();
	void playerWithTile();
	void playerWithNPC(NPC* npc);
	void playerWithCharacter(Character* character);

	void playerWithItem();

	void enemyWithEnemy(Enemy* enemy);
	void enemyWithTile(Enemy* enemy);
	void detectionPlayer(Enemy* enemy);
	bool detectionPlayer(Enemy* enemy, Player* player);
	bool attackingPlayer(Enemy* enemy, Player* player);

	// ===============애로우 & 이펙트 충돌================
	void effectWithPlayer();
	void collisionTrap(Trap* trap);
	void collisionArrow(Arrow* arrow);

	void bulletWithPlayer(PlasmaBall* plasma);
	void cannonWithPlayer(PlasmaCannon* cannon);
	void spellWithPlayer(SphereSpell* spell);
};
