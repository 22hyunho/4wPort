#pragma once
#include "singletonBase.h"
#include "Effect.h"

class effectManager : public singletonBase<effectManager>
{
private :

	typedef vector<Effect*>				_vEffectList;
	typedef vector<Effect*>::iterator	_viEffectIter;

private :
	_vEffectList	 _vEffect;
	_viEffectIter	 _viEffect;

public :
	effectManager() {};
	~effectManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void addAfterEffect(int frameX, int frameY, float x, float y);
	void addAfterEffect2(int frameX, int frameY, float x, float y);

	void addNullBox(float x, float y, int width, int height);
	void addSlash(float x, float y, int width, int height);
	void addPotExplode(float x, float y, int width, int height);

	void addTransform(float x, float y, bool reverse);

	void addBossEffect1_2(float x, float y, int width, int height);
	void addBossEffect2_1(float x, float y, bool reverse);
	void addBossEffect2_2(float x, float y, bool reverse);

	_vEffectList getVEffect() { return _vEffect; }
	_viEffectIter getVIEffect() { return _viEffect; }
};

