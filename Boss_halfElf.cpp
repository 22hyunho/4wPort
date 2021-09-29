#include "stdafx.h"
#include "bossRoom2.h"
#include "Boss_halfElf.h"
#include "Player.h"

HRESULT Boss_halfElf::init(float x, float y, Player * player)
{
	Boss::init(x, y, player);
	_img = IMAGEMANAGER->addFrameDImage("elf_idle", L"img/boss/halfElf_idle.png", 21, 114, 1, 2);
	IMAGEMANAGER->addFrameDImage("elf_fly", L"img/boss/halfElf_fly1.png", 108, 144, 3, 2);
	IMAGEMANAGER->addFrameDImage("elf_flyingIdle", L"img/boss/halfElf_flyingIdle.png", 144, 144, 4, 2);
	IMAGEMANAGER->addFrameDImage("elf_attack", L"img/boss/halfElf_attack.png", 72, 84, 2, 2);
	IMAGEMANAGER->addFrameDImage("monster_idle", L"img/boss/monster_idle.png", 588, 186, 4, 1);
	IMAGEMANAGER->addFrameDImage("monster_attack1", L"img/boss/monster_attack1.png", 576, 186, 4, 1);
	IMAGEMANAGER->addFrameDImage("monster_attack2", L"img/boss/monster_attack2.png", 900, 219, 4, 1);
	IMAGEMANAGER->addFrameDImage("elf_down", L"img/boss/halfElf_down.png", 36, 72, 1, 2);

	_rc = RectMakeCenter(_x, _y, 36, 72);
	_detection = RectMakeCenter(_x, _y, TILESIZE * 15, TILESIZE * 15);

	_death = false;
	_transform = false;
	_speed = 3;

	_currentHP = _maxHP = 5000;

	_spell = new SphereSpell;
	_spell->init(WINSIZEX, 15);

	_pattern = 1;
	_transformCount = 0;
	return S_OK;
}

void Boss_halfElf::release()
{
}

void Boss_halfElf::update()
{
	_spell->update();
	if (!_transform)
		_rc = RectMakeCenter(_x, _y, 36, 72);
	else
		_rc = RectMakeCenter(_x, _y, 140, 180);

	if (!_transform)
		_detection = RectMakeCenter(_x, _y, TILESIZE * 15, TILESIZE * 15);
	else
		_detection = RectMakeCenter(_x, _y, TILESIZE * 25, TILESIZE * 25);
	if (SCENEMANAGER->getCurrentScene()->getStart()) _start = true;

	switch (_state)
	{
	case BS_IDLE:
		_x = _x;
		_y = _y;

		_individualFrame = 6;
		break;

	case BS_MOVE:
		_individualFrame = 6;
		if (_start)
		{
			if (_x + 30 < _player->getX())
			{
				_x += _speed;
				_frameY = 0;
			}
			else if (_x - 30 > _player->getX())
			{
				_x -= _speed;
				_frameY = 1;
			}
			if (_y + 30 < _player->getY())
			{
				_y += _speed;
			}
			else if (_y - 30 > _player->getY())
			{
				_y -= _speed;
			}
		}
		break;

	case BS_ATTACK:
		_individualFrame = 10;

		if (!_transform)
		{
			if (_coolDown) changeState(BS_MOVE);

			else
			{
				_attackCount++;

				if (_attackCount > 80)
				{
					for (int i = 0; i < 5; i++)
					{
						_spell->fire(_x, _y, getAngle(_x, _y, _player->getX(), _player->getY()) - TORADIAN(10) + TORADIAN(i * 5));
					}
					_coolDown = true;
					_attackCount = 0;
				}
			}
		}
		else
		{
			_rndCount++;
			if (_rndCount > 121)
			{
				_rnd = rand() % 2;
				_rndCount = 0;
			}
			if (_coolDown) changeState(BS_MOVE);

			else
			{
				_attackCount++;

				if (_rnd == 0)
				{
					if (_attackCount > 60)
					{

						for (int i = 0; i < 7; i++)
						{
							_spell->fire(_x, _y, getAngle(_x, _y, _player->getX(), _player->getY()) - TORADIAN(30) + TORADIAN(i * 10));
						}

						_coolDown = true;
						_attackCount = 0;
					}
				}
				else
				{
					if (_attackCount == 30)
					{
						for (int i = 0; i < 5; i++)
							for (int j = 0; j < 5; j++)
							{
								_effectX = _player->getX() - TILESIZE * 2 + TILESIZE * j;
								_effectY = _player->getY() - TILESIZE * 2 + TILESIZE * i;
								EFFECTMANAGER->addBossEffect2_1(_player->getX() - TILESIZE * 2 + TILESIZE * j,
									_player->getY() - TILESIZE * 2 + TILESIZE * i, false);
							}
					}
					if (_attackCount > 60)
					{
						for (int i = 0; i < 5; i++)
							for (int j = 0; j < 5; j++)
							EFFECTMANAGER->addBossEffect2_2(_effectX - TILESIZE * j, _effectY - TILESIZE * i, false);
							_coolDown = true;
						_attackCount = 0;
					}
				}
			}
		}

		break;

	case BS_HURT :
		changeState(BS_MOVE);
		break;

	case BS_DYING:
		_dying = true;
		_transform = false;
		break;
	}

	if (_coolDown) _coolDownCount++;
	if (_coolDownCount > 150)
	{
		_coolDown = false;
		_coolDownCount = 0;
	}

	detection();

	if (_currentHP <= _maxHP * 0.5 && !_transform && !_dying && !_death)
	{
		_invincible = true;
		changeState(BS_IDLE);
		_transformCount++;
		if (_transformCount <= 2)
			EFFECTMANAGER->addTransform(_x, _y - 20, true);
		if (_transformCount >= 180)
		{
			_invincible = false;
			_transform = true;
			_transformCount = 0;
		}
	}

	if (_dying)
	{
		_frameX = 0;
		_dyingCount++;
		if (_dyingCount <= 2)
			EFFECTMANAGER->addTransform(_x, _y - 20, false);
		if (_dyingCount >= 180)
		{
			_death = true;
			_dying = false;
		}
	}
}

void Boss_halfElf::render()
{
	if (!_transform)
		_img->frameRender(_rc.left, _rc.top, _frameX, _frameY);
	else
		_img->frameRender(_rc.left, _rc.top, _frameX, 0);

	if (PRINTMANAGER->isDebug())
	{
		DTDMANAGER->Rectangle(_rc);
		DTDMANAGER->Rectangle(_detection);
		DTDMANAGER->Rectangle(_detection2);
	}
	_spell->render();

	if (PRINTMANAGER->isDebug())
	{
		WCHAR str[128];
		swprintf_s(str, L"state : %d", _state);
		DTDMANAGER->printText(str, _x, _y - 70, 150, 20);
		swprintf_s(str, L"atkCount : %d", _attackCount);
		DTDMANAGER->printText(str, _x, _y - 90, 150, 20);
		swprintf_s(str, L"rnd : %d", _rnd);
		DTDMANAGER->printText(str, _x, _y - 110, 150, 20);
	}

	controlFrame();
}

void Boss_halfElf::controlFrame()
{
	_count++;
	if (_count >= _individualFrame)
	{
		if (_frameX >= _img->getMaxFrameX())
		{
			switch (_state)
			{
			case BS_IDLE :
				_frameX = 0;
				break;

			case BS_MOVE :
				_frameX = 0;
				break;

			case BS_ATTACK:
				_frameX = _img->getMaxFrameX();
				break;
			}
		}
		else
			_frameX++;

		_count = 0;
	}
}

void Boss_halfElf::detection()
{
	if (_state != BS_HURT && _state != BS_DYING && !_coolDown)
	{
		RECT rc;
		if (IntersectRect(&rc, &_detection, &_player->getRect()) ||
			IntersectRect(&rc, &_detection2, &_player->getRect()))
		{
			changeState(BS_ATTACK);
		}
		else
			changeState(BS_MOVE);
	}
}

void Boss_halfElf::changeState(BOSSSTATE state)
{
	_state = state;

	switch (_state)
	{
	case BS_IDLE:
		if (!_transform)
			_img = IMAGEMANAGER->findDImage("elf_flyingIdle");
		else
			_img = IMAGEMANAGER->findDImage("monster_idle");
		_frameX = 0;
		break;

	case BS_MOVE:
		if (!_transform)
			_img = IMAGEMANAGER->findDImage("elf_flyingIdle");
		else
			_img = IMAGEMANAGER->findDImage("monster_idle");
		_frameX = 0;
		break;

	case BS_ATTACK:
		if (!_transform)
			_img = IMAGEMANAGER->findDImage("elf_attack");
		else
			_img = IMAGEMANAGER->findDImage("monster_attack1");
		
		_frameX = 0;
		break;

	case BS_DYING:
		_img = IMAGEMANAGER->findDImage("elf_down");
		break;
	}
}
