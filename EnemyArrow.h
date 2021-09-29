#pragma once
struct tagArrow
{
	dImage* img;
	RECT rc;
	float x, y;
	float angle;
	float speed;
	float fireX, fireY;
	int damage;
	int count;
	int index;
};

class PlasmaBall
{
private :
	vector<tagArrow>			_vArrow;
	vector<tagArrow>::iterator _viArrow;

	float _range;
	int _arrowMax;
	int _frameX;
	int _frameY;

public:
	PlasmaBall() {};
	~PlasmaBall() {};

	virtual HRESULT init(float range, int bulletMax);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle);

	void move();
	void remove(int num);

	vector<tagArrow>				getVPlasma() { return _vArrow; }
	vector<tagArrow>::iterator		getVIPlasma() { return _viArrow; }
};

class PlasmaCannon
{
private:
	vector<tagArrow>			_vArrow;
	vector<tagArrow>::iterator _viArrow;

	float _range;
	int _arrowMax;
	int _frameX;
	int _frameY;

public:
	PlasmaCannon() {};
	~PlasmaCannon() {};

	virtual HRESULT init(float range, int bulletMax);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle);

	void move();
	void remove(int num);

	vector<tagArrow>				getVCannon() { return _vArrow; }
	vector<tagArrow>::iterator		getVICannon() { return _viArrow; }
};

class SphereSpell
{
private:
	vector<tagArrow>			_vArrow;
	vector<tagArrow>::iterator _viArrow;

	float _range;
	int _arrowMax;
	int _frameX;
	int _frameY;

public:
	SphereSpell() {};
	~SphereSpell() {};

	virtual HRESULT init(float range, int bulletMax);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle);

	void move();
	void remove(int num);

	vector<tagArrow>				getVSpell() { return _vArrow; }
	vector<tagArrow>::iterator		getVISpell() { return _viArrow; }
};