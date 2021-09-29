#pragma once
#include "tileInfo.h"


class Maptool
{
private:
	tagCurrentTile _currentTile;
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile _tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];	//Ÿ�ϼӼ�
	
	dImage* _mapTile[13];		//�� ����
	RECT _toolRC;				//���ù�ư ��Ʈ
	RECT _terrainRC[4];			//�ͷ��μӼ� ��Ʈ
	RECT _saveLoad[2];			//���̺�&�ε� ��Ʈ
	RECT _zOrder[4];			//z�� ��Ʈ
	RECT _attr[7];				//Ÿ�ϼӼ� ��Ʈ
	RECT _allTileRC;
	RECT _allMapRC;
	int _pos[2];

	int _width;
	int _height;
	int _ctrSelect;
	int _ctrZ;
	TERRAIN _ctrTerAtt;
	OBJECT _ctrObjAtt;
	int _type;
	int _mouseX, _mouseY;
	int _selectIndexX[2];
	int _selectIndexY[2];
	int _initX, _initY;			//�̹���Ŭ���ο�
	int _endX, _endY;
	int _minimapX, _minimapY;

	const char* _saveDate;

	int _terOrObj;

	bool _tool;
	bool mode;

public:
	Maptool() {};
	~Maptool() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void save(const char * mapName);
	void load(const char * mapName);
	virtual void setup();
	virtual void setSample();
	virtual void setMap();
	virtual void setTool();

	void minimap();
	void imageClipping();

	void allTileBase();
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	dImage* getMaptile() { return _mapTile[4]; }

	DWORD* getTileAttribute() { return _attribute; }

	int getWidth() { return _width; }
	int getHeight() { return _height; }
};

