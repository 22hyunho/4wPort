#include "stdafx.h"
#include "Player.h"
#include "Ellis.h"

HRESULT Player::init()
{
	_x = 100, _y = 100, _z = 1;
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
	_dodgeCount = 0;
	_ctCount = 0;
	_angle = 0;
	_trapCount = 0;
	_boltCount = 0;
	_dodge = false;
	_town = false;
	_hunterCooltime = false;
	_trapCooltime = false;
	_death = false;

	//==============캐릭터================
	_character = new Ellis;
	_character->init();
	_damage = _baseDamage = _character->getDamage();
	_currentHP = _maxHP = _baseHP = _character->getHP();
	_atkSpeed = _baseAts = 40;
	_speed = 4;
	_armor = _stone = 0;
	_coinChance = false;

	//===============무기=================
	_arrow = new arrowManager;
	_arrow->init();
	_trap = new trapManager;
	_trap->init();
	_bearLevel = 1;
	_slowLevel = 1;

	_currentTrap = TRAP_BEAR;
	_currentFood = NULL;

	//=============아티팩트================
	_bread = false;
	_drain = false;
	_leaf = false;

	//기타
	_effectCount = 0;
	_test = 0;
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{	
	if (!_death)controlKey();
	_character->update();
	_trap->update();
	_arrow->update();
	COLLISIONMANAGER->collisionPlayer();

	if (_character->getState() == ST_DIE) _death = true;
	if (_coinChance) _test = 1;
	else             _test = 2;

	if (KEYMANAGER->isOnceKeyDown('K')) this->changeRune(10);
	if (KEYMANAGER->isOnceKeyDown('O')) this->changeGold(10);
}

void Player::render()
{
	_trap->render();
	_arrow->render();
	_character->render(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y));


	if (PRINTMANAGER->isDebug())
	{
		WCHAR str[128];
		swprintf_s(str, L"direct : %d", _direct);
		//DTDMANAGER->printText(str, _x, _rc.top - 50, 150, 20);
		//swprintf_s(str, L"damage : %d", _damage);
		//DTDMANAGER->printText(str, _x, _rc.top - 70, 150, 20);
		//swprintf_s(str, L"speed : %d", _speed);
		//DTDMANAGER->printText(str, _x, _rc.top - 90, 150, 20);
		//swprintf_s(str, L"invCount : %d", _character->getInvCount());
		//DTDMANAGER->printText(str, _x, _rc.top - 110, 150, 20);
		//swprintf_s(str, L"test : %d", _test);
		//DTDMANAGER->printText(str, _x, _rc.top - 130, 150, 20);
		swprintf_s(str, L"x: %d, y: %d", _ptMouse.x, _ptMouse.y);
		DTDMANAGER->printText(str, _ptMouse.x, _ptMouse.y, 150, 0);

		//RECT rc;
		//rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 10, 10);
		//DTDMANAGER->Rectangle(rc);
		//DTDMANAGER->Rectangle(_rc);
	}
	PLAYERUI->render();
}

void Player::plusHP(int value)
{
	_currentHP += value;
	if (_currentHP >= _maxHP) _currentHP = _maxHP;
}

void Player::minusHP(int damage)
{
	if (_armor > 0)
	{
		_armor = 0;
	}
	else if (_armor == 0 && _stone > 0)
	{
		if (_stone > damage)
			_stone -= damage;
		
		else
		{
			_currentHP -= (damage - _stone);
			_stone = 0;
		}
	}
	else if (_armor > 0 && _stone > 0)
	{
		_armor = 0;
	}
	else _currentHP -= damage;
}

void Player::changeCharacter(Character * character)
{
	_character = character;
	_index = character->getIndex();
	_damage = _character->getDamage();
	_currentHP = _maxHP = _character->getHP();
}

void Player::controlKey()
{
	// ==========================================이동==========================================
	_direct = 0;
	_boltCount++;
	if (KEYMANAGER->isStayKeyDown(KEY_LEFT))
	{
		if (_character->getState() != ST_AIMING && !_character->getDodge())
		{
			if (_character->getIndex() == CH_HUNTER && _character->getState() != ST_SHOOT)
			{
				_direct |= LEFT;
				_character->setFrameY(1);
				_character->changeState(ST_RUN);
			}
			else if (_character->getIndex() == CH_XBOW)
			{
				_direct |= LEFT;
				_character->setFrameY(1);
				_character->changeState(ST_RUN);
			}
		}
	}
	else if (KEYMANAGER->isStayKeyDown(KEY_RIGHT))
	{
		if (_character->getState() != ST_AIMING && !_character->getDodge())
		{
			if (_character->getIndex() == CH_HUNTER && _character->getState() != ST_SHOOT)
			{
				_direct |= RIGHT;
				_character->setFrameY(0);
				_character->changeState(ST_RUN);
			}
			else if (_character->getIndex() == CH_XBOW)
			{
				_direct |= RIGHT;
				_character->setFrameY(0);
				_character->changeState(ST_RUN);
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(KEY_UP))
	{
		if (_character->getState() != ST_AIMING && !_character->getDodge())
		{
			if (_character->getIndex() == CH_HUNTER && _character->getState() != ST_SHOOT)
			{
				_direct |= UP;
				_character->changeState(ST_RUN);
			}
			else if (_character->getIndex() == CH_XBOW)
			{
				_direct |= UP;
				_character->changeState(ST_RUN);
			}
		}
	}
	else if (KEYMANAGER->isStayKeyDown(KEY_DOWN))
	{
		if (_character->getState() != ST_AIMING && !_character->getDodge())
		{
			if (_character->getIndex() == CH_HUNTER && _character->getState() != ST_SHOOT)
			{
				_direct |= DOWN;
				_character->changeState(ST_RUN);
			}
			else if (_character->getIndex() == CH_XBOW)
			{
				_direct |= DOWN;
				_character->changeState(ST_RUN);
			}
		}
	}

	if (_direct != 0) move();

	if ((KEYMANAGER->isOnceKeyUp(KEY_LEFT) || KEYMANAGER->isOnceKeyUp(KEY_RIGHT) ||
		KEYMANAGER->isOnceKeyUp(KEY_UP) || KEYMANAGER->isOnceKeyUp(KEY_DOWN)) && !_character->getDodge())
		_character->changeState(ST_IDLE);

	// ==========================================공격==========================================
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_town && !_character->getDodge())
	{
		if (_ptMouse.x > _x)		_character->setFrameY(0);
		else if (_ptMouse.x < _x)	_character->setFrameY(1);
		switch (_index)
		{
		case CH_HUNTER :
			if (!_hunterCooltime)_character->changeState(ST_AIMING);
			break;


		case CH_XBOW :
			if (_direct != 0)
				_character->changeState(ST_MOVINGSHOOT);
			else
			_character->changeState(ST_SHOOT);

			if (_boltCount >= _atkSpeed)
			{
				if (!_leaf)
				_arrow->shootXbow(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y));

				else
				{
					_arrow->shootXbow(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y) + TORADIAN(5));
					_arrow->shootXbow(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y) - TORADIAN(5));
				}
				_boltCount = 0;
			}
			break;
		}
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && !_town && !_character->getDodge())
	{
		switch (_index)
		{
		case CH_HUNTER:
			if (!_hunterCooltime) {
				_character->changeState(ST_SHOOT);
				if (!_leaf)
					_arrow->shootHunter(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y));
				
				else
				{
					_arrow->shootHunter(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y) + TORADIAN(5));
					_arrow->shootHunter(_x, _y, getAngle(_x, _y, _ptMouse.x, _ptMouse.y) - TORADIAN(5));
				}

				_hunterCooltime = true;
			}
			break;
		case CH_XBOW:
			_character->changeState(ST_IDLE);
			break;
		}
	}
	if (_hunterCooltime) _ctCount++;
	if (_ctCount >= 60)
	{
		_hunterCooltime = false;
		_ctCount = 0;
	}

	// ==========================================회피==========================================
	if (KEYMANAGER->isOnceKeyDown(KEY_DODGE) && !_character->getDodge())
	{
		_character->changeState(ST_DODGE);
	}
	if (_character->getDodge())
	{
		moveDodge();
		_effectCount++;
		if (_character->getIndex() == CH_HUNTER)
		{
			if (_effectCount > 10)
			{
				EFFECTMANAGER->addAfterEffect2(_character->getFrameX(), _character->getDirect(), _x, _y);
				_effectCount = 0;
			}
		}
		else if (_character->getIndex() == CH_XBOW)
		{
			if (_effectCount > 3)
			{
				EFFECTMANAGER->addAfterEffect(0, _character->getDirect(), _x, _y);
				_effectCount = 0;
			}
		}
	}

	// ==========================================트랩==========================================
	if (KEYMANAGER->isOnceKeyDown(KEY_TRAP) && !_town && !_trapCooltime)
	{
		_trapCooltime = true;
		_character->changeState(ST_DEPLOY);
		switch (_currentTrap)
		{
		case TRAP_BEAR :
			_trap->deployBearTrap(_x, _y, PointMake(_ptMouse.x, _ptMouse.y), _bearLevel);
			break;
		case TRAP_SLOW :
			_trap->deploySlowTrap(_x, _y, PointMake(_ptMouse.x, _ptMouse.y), _slowLevel);
			break;
		}
	}

	if (_trapCooltime)
	{
		_trapCount++;
		if (_trapCount >= 300)
		{
			_trapCooltime = false;
			_trapCount = 0;
		}
	}
	
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
}

void Player::move()
{
	switch (_direct)
	{
	case 1:		//RIGHT
		_angle = 0;
		break;
	case 2:		//LEFT
		_angle = PI;
		break;

	case 4:		//UP
		_angle = PI / 2;
		break;
	case 5:		//UPRIGHT
		_angle = PI / 4;
		break;
	case 6:		//UPLEFT
		_angle = 3 * PI / 4;
		break;

	case 8:		//DOWN
		_angle = 3 * PI2 / 4;
		break;
	case 9:		//DOWNRIGHT
		_angle = 7 * PI2 / 8;
		break;
	case 10:	//DOWNLEFT
		_angle = 5 * PI2 / 8;
		break;

	default:
		_angle = 0;
		break;
	}
	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;

	if (_currentHP <= 0) _character->changeState(ST_DIE);
}

void Player::downStair()
{
	_y += 0.35f;
	_rc = RectMakeCenter(_x, _y, TILESIZE / 2, TILESIZE);
}

void Player::moveDodge()
{
	switch (_index)
	{
	case CH_HUNTER :
		_x += cosf(_angle) * 8;
		_y += -sinf(_angle) * 8;
		break;

	case CH_XBOW :
		_x += cosf(_angle) * 15;
		_y += -sinf(_angle) * 15;
		break;
	}
}
