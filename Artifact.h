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
	dImage*			_img;		//�̹���
	RECT			_rc;		//��Ʈ
	wstring			_name;		//ǥ�ÿ� �̸�
	wstring			_info;		//������ �Ұ�
	ARTIFACTLIST	_type;		//������ Ÿ��
	float			_x, _y;		//�ѷ����� ��ǥ��
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

	//=====================������&������=====================
	RECT getRect() { return _rc; }

	wstring getName() { return _name; }

	wstring getInfo() { return _info; }

	dImage* getImage() { return _img; }

	ARTIFACTLIST getType() { return _type; }
};

