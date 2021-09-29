#include "stdafx.h"
#include "collisionManager.h"
#include "Scene.h"
#include "Player.h"
#include "Character.h"
#include "NPC.h"
#include "enemyManager.h"


HRESULT collisionManager::init(Scene * scene)
{
	_scene = scene;
	_allTile = TILEMANAGER->getTile();

	return S_OK;
}

HRESULT collisionManager::init(Player * player)
{
	_player = player;
	_kill = 0;
	return S_OK;
}

HRESULT collisionManager::init(enemyManager * enemy)
{
	_em = enemy;
	_eX = 0;
	_eY = 0;
	return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::collisionPlayer()
{
	playerWithTile();
	playerWithItem();
}

void collisionManager::playerWithTile()
{
	float x = _player->getX();
	float y = _player->getY();

	int initY = y / TILESIZE - 2;
	int endY = y / TILESIZE + 2;
	int initX = x / TILESIZE - 2;
	int endX = x / TILESIZE + 2;

	//예외처리
	if (initY < 0)
		initY = 0;
	if (initX < 0)
		initX = 0;

	int width = TILEMANAGER->getWidth();
	RECT rc;

	int i, j;

	for (i = initY, j = initX; i <= endY; j++) {
		int index = i * width + j;
		
		if ((_allTile[index].terrain == TR_BLOCK || _allTile[index].obj == OBJ_BLOCK) &&
			IntersectRect(&rc, &_allTile[index].rc, &_player->getRect()))
		{

			float width = rc.right - rc.left;
			float height = rc.bottom - rc.top;
			float x = (_allTile[index].rc.left + _allTile[index].rc.left) / 2;
			float y = (_allTile[index].rc.bottom + _allTile[index].rc.top) / 2;

			//좌우 충돌
			if (height > width) {
				//좌
				if (_player->getX() < x) {
					_player->setX(_player->getX() - width - 1);
				}
				//우
				else {
					_player->setX(_player->getX() + width);
				}
			}
			//상하 충돌
			else if (width > height) {
				//아래
				if (_player->getY() > y)
				{	
					_player->setY(_player->getY() + height);
				}
				//위
				else
				{
					_player->setY(_player->getY() - height);
				}
			}
			_player->setRect(_player->getX(), _player->getY(), TILESIZE / 2, TILESIZE);
		}

		if (j >= endX) {
			i++;
			j = initX - 1;
		}
	}
}

void collisionManager::playerWithNPC(NPC * npc)
{
	RECT rc;
	if (IntersectRect(&rc, &_player->getRect(), &npc->getRect()))
	{
		float width = rc.right - rc.left;
		float height = rc.bottom - rc.top;

		//좌우 충돌
		if (height > width) {
			//좌
			if (_player->getX() < npc->getX()) {
				_player->setX(_player->getX() - width);
			}
			//우
			else {
				_player->setX(_player->getX() + width);
			}
		}
		//상하 충돌
		else if (width > height) {
			//아래
			if (_player->getY() > npc->getY())
			{
				_player->setY(_player->getY() + height);
			}
			//위
			else
			{
				_player->setY(_player->getY() - height);
			}
		}

		_player->setRect(_player->getX(), _player->getY(), TILESIZE / 2, TILESIZE);
	}
}

void collisionManager::playerWithCharacter(Character * character)
{
	RECT rc;
	if (IntersectRect(&rc, &_player->getRect(), &character->getRect()) && _player->getIndex() != character->getIndex())
	{
		float width = rc.right - rc.left;
		float height = rc.bottom - rc.top;

		//좌우 충돌
		if (height > width) {
			//좌
			if (_player->getX() < character->getX()) {
				_player->setX(_player->getX() - width);
			}
			//우
			else {
				_player->setX(_player->getX() + width);
			}
		}
		//상하 충돌
		else if (width > height) {
			//아래
			if (_player->getY() > character->getY())
			{
				_player->setY(_player->getY() + height);
			}
			//위
			else
			{
				_player->setY(_player->getY() - height);
			}
		}

		_player->setRect(_player->getX(), _player->getY(), TILESIZE / 2, TILESIZE);
	}
}

void collisionManager::playerWithItem()
{
	RECT temp;
	for (int i = 0; i < ITEMMANAGER->getVItem().size(); i++)
	{
		if (IntersectRect(&temp, &_player->getRect(), &ITEMMANAGER->getVItem()[i]->getRect()))
		{
			switch (ITEMMANAGER->getVItem()[i]->getType())
			{
			case TY_GOLD : 
				_player->changeGold(ITEMMANAGER->getVItem()[i]->getValue());
				break;

			case TY_RUNE :
				_player->changeDRune(ITEMMANAGER->getVItem()[i]->getValue());
				break;

			case TY_MEAT :
				if (_player->getBread())
					_player->plusHP(ITEMMANAGER->getVItem()[i]->getValue() * 2);
				else
					_player->plusHP(ITEMMANAGER->getVItem()[i]->getValue());
				break;
			}
			ITEMMANAGER->remove(i);
		}
	}
		
	
	
}

void collisionManager::enemyWithEnemy(Enemy * enemy)
{
}

void collisionManager::enemyWithTile(Enemy * enemy)
{
	_eX = enemy->getX();
	_eY = enemy->getY();
	
	int initY = _eY / TILESIZE - 2;
	int endY = _eY / TILESIZE + 2;
	int initX = _eX / TILESIZE - 2;
	int endX = _eX / TILESIZE + 2;

	//예외처리
	if (initY < 0)
		initY = 0;
	if (initX < 0)
		initX = 0;

	int width = TILEMANAGER->getWidth();
	RECT rc;

	int i, j;

	for (i = initY, j = initX; i <= endY; j++) {
		int index = i * width + j;

		if ((_allTile[index].terrain == TR_BLOCK || _allTile[index].obj == OBJ_BLOCK) &&
			IntersectRect(&rc, &_allTile[index].rc, &enemy->getRect()))
		{

			float width = rc.right - rc.left;
			float height = rc.bottom - rc.top;
			float x = (_allTile[index].rc.left + _allTile[index].rc.left) / 2;
			float y = (_allTile[index].rc.bottom + _allTile[index].rc.top) / 2;

			//좌우 충돌
			if (height > width) {
				//좌
				if (enemy->getX() < x) {
					enemy->setX(enemy->getX() - width - 1);
				}
				//우
				else {
					enemy->setX(enemy->getX() + width);
				}
			}
			//상하 충돌
			else if (width > height) {
				//아래
				if (enemy->getY() > y)
				{
					enemy->setY(enemy->getY() + height);
				}
				//위
				else
				{
					enemy->setY(enemy->getY() - height);
				}
			}
		}

		if (j >= endX) {
			i++;
			j = initX - 1;
		}

	}
}

void collisionManager::detectionPlayer(Enemy* enemy)
{
	RECT rc;
		if (!_player->getDeath() && enemy->getState() != ES_DIE &&
			IntersectRect(&rc, &_player->getRect(), &enemy->getDetection()))
		{
			enemy->setEndX(_player->getX());
			enemy->setEndY(_player->getY());
			if (enemy->getState() != ES_HURT && enemy->getState() != ES_ATTACK && enemy->getState() != ES_COOLDOWN &&
				enemy->getState() != ES_DIE)
			{
				switch (enemy->getType())
				{
				case TY_MELEE :
					enemy->setState(ES_MOVE);
					break;

				case TY_RANGE :
					enemy->setState(ES_MOVE);
					break;
				}
			}
		}

		if (!_player->getDeath() && enemy->getState() != ES_DIE &&
			IntersectRect(&rc, &_player->getRect(), &enemy->getAttackBox()))
		{
			enemy->setEndX(_player->getX());
			enemy->setEndY(_player->getY());
			if (enemy->getState() != ES_HURT && enemy->getState() != ES_ATTACK && enemy->getState() != ES_COOLDOWN &&
				enemy->getState() != ES_DIE)
			{
				enemy->changeState(ES_ATTACK);
			}
		}
	
}

bool collisionManager::detectionPlayer(Enemy * enemy, Player * player)
{
	RECT rc;
	if (!_player->getDeath() && enemy->getState() != ES_DIE &&
		IntersectRect(&rc, &_player->getRect(), &enemy->getDetection()))
		return true;

	return false;
}

bool collisionManager::attackingPlayer(Enemy * enemy, Player * player)
{
	RECT rc;
	if (!_player->getDeath() && enemy->getState() != ES_DIE &&
		IntersectRect(&rc, &_player->getRect(), &enemy->getAttackBox()))
		return true;

	return false;
}

void collisionManager::effectWithPlayer()
{
	RECT rc;
	for (int i = 0; i < EFFECTMANAGER->getVEffect().size(); i++)
	{
		if (EFFECTMANAGER->getVEffect()[i]->getType() == EF_ATTACK && !_player->getCharacter()->getDodge() &&
			IntersectRect(&rc, &_player->getRect(), &EFFECTMANAGER->getVEffect()[i]->getRect()))
		{
			CAMERAMANAGER->vibrateScreen(_player->getX(), _player->getY(), 5.f, 0.05f);
			if (!_player->getCharacter()->getInvincible() && !_player->getDeath())
			{
				_player->minusHP(EFFECTMANAGER->getVEffect()[i]->getDamage());
				_player->getCharacter()->changeState(ST_HURT);
				_player->getCharacter()->setInvincible(true);
				if (_player->getCurrentHP() <= 0) _player->getCharacter()->changeState(ST_DIE);
			}
		}
	}
}

void collisionManager::bulletWithPlayer(PlasmaBall * plasma)
{
	RECT rc;
	for (int i = 0; i < plasma->getVPlasma().size(); i++)
	{
		if (IntersectRect(&rc, &_player->getRect(), &plasma->getVPlasma()[i].rc))
		{
			CAMERAMANAGER->vibrateScreen(_player->getX(), _player->getY(), 5.f, 0.05f);
			if (!_player->getCharacter()->getInvincible() && !_player->getDeath())
			{
				_player->minusHP(plasma->getVPlasma()[i].damage);
				_player->getCharacter()->changeState(ST_HURT);
				_player->getCharacter()->setInvincible(true);
			}
			plasma->remove(i);
		}
	}
}

void collisionManager::cannonWithPlayer(PlasmaCannon * cannon)
{
	RECT rc;
	for (int i = 0; i < cannon->getVCannon().size(); i++)
	{
		if (IntersectRect(&rc, &_player->getRect(), &cannon->getVCannon()[i].rc))
		{
			EFFECTMANAGER->addBossEffect1_2(cannon->getVCannon()[i].x, cannon->getVCannon()[i].y, 0, 0);
			cannon->remove(i);
		}
	}
}

void collisionManager::spellWithPlayer(SphereSpell * spell)
{
	RECT rc;
	for (int i = 0; i < spell->getVSpell().size(); i++)
	{
		if (IntersectRect(&rc, &_player->getRect(), &spell->getVSpell()[i].rc))
		{
			CAMERAMANAGER->vibrateScreen(_player->getX(), _player->getY(), 5.f, 0.05f);
			if (!_player->getCharacter()->getInvincible() && !_player->getDeath())
			{
				_player->minusHP(spell->getVSpell()[i].damage);
				_player->getCharacter()->changeState(ST_HURT);
				_player->getCharacter()->setInvincible(true);
			}
			spell->remove(i);
		}
	}
}

void collisionManager::collisionTrap(Trap* trap)
{
	RECT rc;
	for (int i = 0; i < _em->getVEnemy().size(); i++)
		if (trap->getDeploy() && !trap->getUnfold() && trap->getType() == BEARTRAP &&
			IntersectRect(&rc, &_em->getVEnemy()[i]->getRect(), &trap->getRect()))
		{
			_em->getVEnemy()[i]->changeHP(trap->getDamage());
			trap->setUnfold(true);

			if (_em->getVEnemy()[i]->getCurrentHP() <= 0)
			{
				_em->getVEnemy()[i]->changeState(ES_DIE);
				if (_player->getDrain())
				{
					_kill++;
					if (_kill >= 2)
					{
						_player->plusHP(1);
						_kill = 0;
					}
				}
			}
		}

	for (int i = 0; i < _em->getVEnemy().size(); i++)
		if (trap->getDeploy() && trap->getType() == SLOWTRAP &&
			IntersectRect(&rc, &_em->getVEnemy()[i]->getRect(), &trap->getRect()))
		{
			_em->getVEnemy()[i]->setSpeed(1);
		}
		

	for (int i = 0; i < _em->getVBoss().size(); i++)
		if (trap->getDeploy() && !trap->getUnfold() && trap->getType() == BEARTRAP &&
			IntersectRect(&rc, &_em->getVBoss()[i]->getRect(), &trap->getRect()))
		{
			_em->getVEnemy()[i]->changeHP(trap->getDamage());
			trap->setUnfold(true);
			_em->getVEnemy()[i]->changeState(ES_HURT);

			if (_em->getVBoss()[i]->getCurrentHP() <= 0)
				_em->getVBoss()[i]->changeState(BS_DYING);
		}
}

void collisionManager::collisionArrow(Arrow* arrow)
{
	RECT rc;
	int width = TILEMANAGER->getWidth();
	int height = TILEMANAGER->getHeight();
	for (int i = 0; i < width * height; i++)
		if ((_allTile[i].terrain == TR_BLOCK || _allTile[i].obj == OBJ_BLOCK) &&
			IntersectRect(&rc, &arrow->getRect(), &_allTile[i].rc))
		{
			arrow->setOff(true);
		}

	if (_em->getVEnemy().size() > 0)
	{
		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			if (_em->getVEnemy()[i]->getState() == ES_DIE) continue;

			if (IntersectRect(&rc, &arrow->getRect(), &_em->getVEnemy()[i]->getRect()))
			{
				arrow->setOff(true);

				_em->getVEnemy()[i]->changeHP(_player->getDamage());
				_em->getVEnemy()[i]->setFrameX(0);
				_em->getVEnemy()[i]->changeState(ES_HURT);
				_em->getVEnemy()[i]->knockBack
				(getAngle(_player->getX(), _player->getY(),
					_em->getVEnemy()[i]->getX(), _em->getVEnemy()[i]->getY()));

				if (_em->getVEnemy()[i]->getCurrentHP() <= 0)
				{
					_em->getVEnemy()[i]->changeState(ES_DIE);
					if (_player->getDrain())
					{
						_kill++;
						if (_kill >= 2)
						{
							_player->plusHP(1);
							_kill = 0;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < _em->getVBoss().size(); i++)
	{
		if (IntersectRect(&rc, &arrow->getRect(), &_em->getVBoss()[i]->getRect()))
		{
			arrow->setOff(true);
			if (!_em->getVBoss()[i]->getInv())
			{
				_em->getVBoss()[i]->changeHP(2500);
				_em->getVBoss()[i]->changeState(BS_HURT);
			}

			if (_em->getVBoss()[i]->getCurrentHP() <= 0)
				_em->getVBoss()[i]->changeState(BS_DYING);
		}
	}
}
