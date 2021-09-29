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
	tagTile* _allTile;		//Ÿ�� ���
	vector<Item*>* _allItem;		//������ ���

	float _eX, _eY;
	int _kill;
	//�浹�ϴ� ��ü�� �ľ��ϱ�
	//�÷��̾�� ���ʹ�
	//�÷��̾�� ������

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

	// ===============�ַο� & ����Ʈ �浹================
	void effectWithPlayer();
	void collisionTrap(Trap* trap);
	void collisionArrow(Arrow* arrow);

	void bulletWithPlayer(PlasmaBall* plasma);
	void cannonWithPlayer(PlasmaCannon* cannon);
	void spellWithPlayer(SphereSpell* spell);
};
