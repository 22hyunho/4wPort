#pragma once

class Player;

class Menu
{
protected:
	Player* _player;
	dImage* _back;
	dImage* _border[2];
	D2D1_RECT_F _screen;

	float _tuningX;
	float _tuningY;

	int _index;
	bool _hidden;
	bool _buy[9];
public:
	Menu() {};
	~Menu() {};

	virtual HRESULT init(Player* player);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render();

	//=====================접근자&설정자=====================

	bool getHidden() { return _hidden; }
	void setHidden(bool hidden) { _hidden = hidden; }

	bool getBuy() { return _buy; }
};

