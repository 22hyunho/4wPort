#include "stdafx.h"
#include "playerUI.h"
#include "Player.h"

HRESULT playerUI::init(Player * player)
{
	_player = player;

	for (int i = 0; i < 10; i++)
	{
		_heart[i] = IMAGEMANAGER->addDImage("heart", L"img/ui/heart.png", 48, 48);
		_half[i] = IMAGEMANAGER->addDImage("halfHeart", L"img/ui/halfHeart.png", 48, 48);
	}
	for (int i = 0; i < 2; i++)
	{
		_stone[i] = IMAGEMANAGER->addDImage("stone", L"img/ui/stone.png", 48, 48);
	}
	_armor = IMAGEMANAGER->addDImage("armor", L"img/ui/armor.png", 48, 48);
	_gold = IMAGEMANAGER->addDImage("gold_ui", L"img/ui/gold_ui.png", 50, 65);
	_rune = IMAGEMANAGER->addDImage("rune_ui", L"img/ui/rune_ui.png", 54, 65);
	_keyQ = IMAGEMANAGER->addDImage("key_Q", L"img/ui/keyboard_Q.png", 44, 44);
	return S_OK();
}

void playerUI::release()
{
}

void playerUI::update()
{
}

void playerUI::render()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	for (int i = 0; i < (_player->getCurrentHP() + 1) / 2; i++)
	{
		_half[i]->render(screen.left + 20 + i * 60, screen.top + 10);
	}
	for (int i = 0; i < _player->getCurrentHP() / 2; i++)
	{
		_heart[i]->render(screen.left + 20 + i * 60, screen.top + 10);
	}
	for (int i = 0; i < _player->getStone(); i++)
	{
		_stone[i]->render(screen.left + 20 + i * 60, screen.top + 70);
	}
	if (_player->getArmor() > 0)
		_armor->render(screen.left + 140, screen.top + 70);

	if (INVENTORY->getVArtifact().size() > 0)
	{
		for (int i = 0; i < INVENTORY->getVArtifact().size(); i++)
		{
			INVENTORY->getVArtifact()[i]->getImage()->render(screen.left + 50 + i * 120, screen.bottom - 130, 0.4f);
		}
	}

	_gold->render(screen.left + 20, screen.top + 140);
	_rune->render(screen.left + 175, screen.top + 135);
	WCHAR str[128];
	swprintf_s(str, L"%d", _player->getGold());
	DTDMANAGER->printText(str, screen.left + 130, screen.top + 170, 100, 20, 40);
	if (_player->getTown())
	{
		swprintf_s(str, L"%d", _player->getRune());
		DTDMANAGER->printText(str, screen.left + 290, screen.top + 170, 100, 20, 40);
	}
	else
	{
		swprintf_s(str, L"%d", _player->getDRune());
		DTDMANAGER->printText(str, screen.left + 290, screen.top + 170, 100, 20, 40);
	}

	_keyQ->render(screen.left + 20, screen.top + 220);
	_trap->render(screen.left + 80, screen.top + 220, _alpha);

	if (!_player->getTrapCool()) _alpha = 1.0f;
	else
	{
		for (int i = 0; i < 10; i++)
			if (_player->getTrapTime() / 30 == i)
			{
				_alpha = 0.1f * i;
			}
	}
}
