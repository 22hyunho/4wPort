#pragma once
#include "tileInfo.h"


class Maptool
{
private:
	tagCurrentTile _currentTile;
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile _tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];	//타일속성
	
	dImage* _mapTile[13];		//맵 샘플
	RECT _toolRC;				//샘플버튼 렉트
	RECT _terrainRC[4];			//터레인속성 렉트
	RECT _saveLoad[2];			//세이브&로드 렉트
	RECT _zOrder[4];			//z축 렉트
	RECT _attr[7];				//타일속성 렉트
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
	int _initX, _initY;			//이미지클리핑용
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

