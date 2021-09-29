#pragma once

class Player;
enum ARTIFACTLIST
{
	ART_ANVIL,
	ART_BOOTS,
	ART_BREAD,
	ART_COFFEE,
	ART_DRAINBITE,
	ART_EGGPLANT,
	ART_GLOVE,
	ART_LEAF,
	ART_MILK,
	ART_STRONGBOLT,
	ART_TEAR
};

class Artifact
{
protected :
	dImage*			_img;		//이미지
	RECT			_rc;		//렉트
	wstring			_name;		//표시용 이름
	wstring			_info;		//아이템 소개
	ARTIFACTLIST	_type;		//아이템 타입
	float			_x, _y;		//뿌려지는 좌표값
	int				_count;
	bool			_off;

public :
	Artifact() {};
	~Artifact() {};

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(Player* player) = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//=====================접근자&설정자=====================
	RECT getRect() { return _rc; }

	wstring getName() { return _name; }

	wstring getInfo() { return _info; }

	dImage* getImage() { return _img; }

	ARTIFACTLIST getType() { return _type; }
};

