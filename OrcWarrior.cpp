#include "stdafx.h"
#include "OrcWarrior.h"
#include "Player.h"

HRESULT OrcWarrior::init(float x, float y, Player * player)
{
	Enemy::init(x, y, player);
	_type = TY_MELEE;
	_currentHP = _maxHP = 120;
	_img = IMAGEMANAGER->addFrameDImage("orc2_idle", L"img/enemy/orc/orc2_idle.png", 264, 96, 4, 2);
	IMAGEMANAGER->addFrameDImage("orc2_run", L"img/enemy/orc/orc2_run.png", 276, 102, 4, 2);
	IMAGEMANAGER->addFrameDImage("orc2_attack", L"img/enemy/orc/orc2_attack.png", 126, 102, 2, 2);
	IMAGEMANAGER->addFrameDImage("orc2_cooldown", L"img/enemy/orc/orc2_cooldown.png", 264, 78, 4, 2);
	IMAGEMANAGER->addFrameDImage("orc2_die", L"img/enemy/orc/orc2_die.png", 54, 72, 1, 2);

	_rc = RectMakeCenter(_x, _y, 45, 48);
	_speed = 4;
	return S_OK;
}

void OrcWarrior::release()
{
}

void OrcWarrior::update()
{
	Enemy::update();

	switch (_state)
	{
	case ES_IDLE:
		_img = IMAGEMANAGER->findDImage("orc2_idle");
		_individualFrame = 0.15f;
		_tuningX = -10;
		break;

	case ES_MOVE:
		_img = IMAGEMANAGER->findDImage("orc2_run");
		_individualFrame = 0.06f;
		break;

	case ES_ATTACK:
		_img = IMAGEMANAGER->findDImage("orc2_attack");
		_individualFrame = 0.1f;
		if (_coolDown)
			changeState(ES_COOLDOWN);

		else
		{
			if (_frameX < 1)
				EFFECTMANAGER->addNullBox(_x, _y, TILESIZE * 3, TILESIZE * 3);
		}
		break;

	case ES_COOLDOWN :
		_img = IMAGEMANAGER->findDImage("orc2_cooldown");
		_individualFrame = 0.1f;

	case ES_HURT:
		_hurtCount++;
		if (_hurtCount > 50)
		{
			changeState(ES_IDLE);
			_hurtCount = 0;
		}
		break;

	case ES_DIE:
		_img = IMAGEMANAGER->findDImage("orc2_die");
		_dieCount++;
		if (_dieCount > 120)
		{
			int rnd = 0;
			int rnd2 = 0;
			rnd = RND->getFromIntTo(1, 101);
			rnd2 = RND->getInt(3);

			if (rnd > 60 && rnd2 == 0)
				ITEMMANAGER->dropRune(_x, _y, 0, RND->getFromIntTo(1, 5));

			else if (rnd > 60 && rnd2 == 1)
			{
				if (!_player->getChance())
					ITEMMANAGER->dropGold(_x, _y, 0, RND->getFromFloatTo(1, 5));
				else
					ITEMMANAGER->dropGold(_x, _y, 0, RND->getFromFloatTo(5, 11));
			}

			else if (rnd > 60 && rnd2 == 2)
				ITEMMANAGER->dropMeat(_x, _y, 0, 0);
			_death = true;
		}
		break;
	}

	if (_coolDown)
	{
		_coolDownCount++;
		if (_coolDownCount > 100)
		{
			_coolDown = false;
			_coolDownCount = 0;
		}
	}
	_rc = RectMakeCenter(_x, _y, 45, 48);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 10, TILESIZE * 10);
	_attackBox = RectMakeCenter(_x, _y, TILESIZE * 2, TILESIZE * 2);
}

void OrcWarrior::render()
{
	_img->frameRender(_rc.left + _tuningX, _rc.top + _tuningY, _frameX, _frameY);

	controlFrame();

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_detection);
		DTDMANAGER->Rectangle(_attackBox);
		WCHAR str[128];
		swprintf_s(str, L"x : %f y : %f", _x, _y);
		DTDMANAGER->printText(str, _x, _rc.top - 20, 150, 20);
	}
}

void OrcWarrior::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= _individualFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			if (_state == ES_ATTACK)
				_coolDown = true;

			_frameX = 0;
		}

		else
			_frameX++;

		_count = 0;
	}
}

void OrcWarrior::changeState(ENEMYSTATE state)
{
	_state = state;
	_frameX = 0;
}
