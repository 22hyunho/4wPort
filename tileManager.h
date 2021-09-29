#pragma once
#include "singletonBase.h"
#include "tileInfo.h"
#include <vector>

#define TILESIZE 48
#define MINITILESIZE 6

#define TILEX 150	//가로 타일 갯수
#define TILEY 150	//세로 타일 갯수


#define TILESIZEX TILESIZE * TILEX	//560 28 * 20
#define TILESIZEY TILESIZE * TILEY	//620 31 * 20

//타일셋 정의
#define SAMPLETILEX 12
#define SAMPLETILEY 6

//비트필드
#define ATTR_UNMOVE 0x00000016	//못가는 타일
#define ATTR_SWAMP	0x00000032	//슬로우 타일
#define ATTR_POISON	0x00000064	//포이즌 타일
#define ATTR_WATER	0x00000128  //물 타일


class tileManager : public singletonBase<tileManager>
{
private:
	dImage* _mapTile[10];
	dImage*	_Obbase;
	dImage* _minibase;

	tagTile _tiles[TILEX*TILEY];
	tagTile _loadTiles[TILEX*TILEY];
	tagTile _mini[TILEX*TILEY];
	DWORD _attribute[TILEX*TILEY];
	

	int _initX;
	int _endX;
	int _initY;
	int _endY;


	int _playerX;
	int _playerY;

	int _width;
	int _height;
	int _type;
	int _floor;
	int _trapCount;
	
	//벡터로 바꿔서 번호만 넣기

public:
	tileManager();
	~tileManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void load(const char* mapName, int width, int height);

	//=====================접근자&설정자=====================
	tagTile* getTile() { return _tiles; }
	tagTile* getLoadTile() { return _loadTiles; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
};

