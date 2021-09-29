#pragma once
#include "Scene.h"
#include "Character.h"
#include "NPC.h"

class town :
	public Scene
{
private :
	Character* _character[2];
	NPC* _NPC[5];
	dImage* _currentTrap;
	dImage* _currentFood;
	RECT _select[2];
	float _frame;
	int _fireX;

	float _tX, _tY;
	float _alpha;
	bool _tUp;

	float _fX, _fY;
	bool _fUp;

	bool _characterSelect;
public :
	town() {};
	~town() {};

	HRESULT init(Player *player);
	void release();
	void update();
	void render();
	void characterChange();
	void equipChange();
	void changeRender();

	void changeScene();
	void changeImage();
	void uiUpdate();
};

