#pragma once

class Player;
class Enemy;

class Pattern
{
protected:
	Player* _player;
	Enemy* _enemy;

public:
	Pattern() {};
	~Pattern() {};

	virtual HRESULT init(Player* player);
	virtual HRESULT init(Enemy* enemy);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

