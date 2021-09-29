#include "stdafx.h"
#include "tileManager.h"

tileManager::tileManager()
{
}

tileManager::~tileManager()
{
}

HRESULT tileManager::init()
{
	//해당 던전의 보스층이 되면
	//보스방 생성하도록
	_mapTile[0] = IMAGEMANAGER->addFrameDImage("forestTile", L"img/map/tiles/forestTile.png", 576, 288, 12, 6);
	_mapTile[1] = IMAGEMANAGER->addFrameDImage("brickTile", L"img/map/tiles/brickTile.png", 576, 288, 12, 6);
	_mapTile[2] = IMAGEMANAGER->addFrameDImage("darkTile", L"img/map/tiles/darkTile.png", 576, 288, 12, 6);
	_mapTile[3] = IMAGEMANAGER->addFrameDImage("cryptTile", L"img/map/tiles/cryptTile.png", 576, 288, 12, 6);
	_mapTile[4] = IMAGEMANAGER->addFrameDImage("townObject1", L"img/map/tiles/town1.png", 576, 288, 12, 6);
	_mapTile[5] = IMAGEMANAGER->addFrameDImage("townObject2", L"img/map/tiles/town2.png", 576, 288, 12, 6);
	_mapTile[6] = IMAGEMANAGER->addFrameDImage("forestObj1", L"img/map/tiles/forest1.png", 576, 288, 12, 6);
	_mapTile[7] = IMAGEMANAGER->addFrameDImage("forestObj2", L"img/map/tiles/forest2.png", 576, 288, 12, 6);
	_mapTile[8] = IMAGEMANAGER->addFrameDImage("brickObj1", L"img/map/tiles/brick1.png", 576, 288, 12, 6);
	_mapTile[9] = IMAGEMANAGER->addFrameDImage("brickObj2", L"img/map/tiles/brick2.png", 576, 288, 12, 6);
	_mapTile[10] = IMAGEMANAGER->addFrameDImage("stair1", L"img/map/tiles/stair1.png", 576, 288, 12, 6);
	_mapTile[11] = IMAGEMANAGER->addFrameDImage("stair2", L"img/map/tiles/stair2.png", 576, 288, 12, 6);
	_mapTile[12] = IMAGEMANAGER->addFrameDImage("stair3", L"img/map/tiles/stair3.png", 576, 288, 12, 6);

	return S_OK;
}

void tileManager::release()
{
}

void tileManager::update()
{
	//이미지 클리핑(렌더 범위/인덱스 설정)
	//->카메라 스크린 기준으로
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_initX = screen.left / TILEWIDTH - 1;
	_endX = screen.right / TILEWIDTH + 1;
	_initY = screen.top / TILEHEIGHT - 1;
	_endY = screen.bottom / TILEHEIGHT + 1;

	if (_initX < 0)
		_initX = 0;
	if (_endX >= _width)
		_endX = _width - 1;
	if (_initY < 0)
		_initY = 0;
	if (_endY >= _height)
		_endY = _height - 1;
}

void tileManager::render()
{
	for (int i = _initY; i <= _endY; i++)
		for (int j = _initX; j <= _endX; j++) {
			int index = i * _width + j;
			
			_mapTile[_tiles[index].terImgIndex]->frameRender(_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].terrainFrameX, _tiles[index].terrainFrameY);
			

			if (PRINTMANAGER->isDebug()) DTDMANAGER->Rectangle(_tiles[index].rc);
		}

	for (int i = _initY; i <= _endY; i++)
		for (int j = _initX; j <= _endX; j++) {
			int index = i * _width + j;

			if (_tiles[index].obj == OBJ_NONE) continue;
			if (_tiles[index].objImg != nullptr)
			{
				_tiles[index].objImg->frameRender(_tiles[index].rc.left, _tiles[index].rc.top,
					_tiles[index].objFrameX, _tiles[index].objFrameY);
			}
			
		}

	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

	if (KEYMANAGER->isToggleKey('Z'))
	for (int i = 0; i < _width * _height; ++i)
	{
		_mapTile[_tiles[i].terImgIndex]->frameRender(
			screen.left + 830 + (_tiles[i].rc.left / (TILESIZE / 3)), 
			screen.top - 130 + (TILESIZE * 3) + (_tiles[i].rc.top / (TILESIZE / 3)),
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY, MINITILESIZE, MINITILESIZE);

		if (_tiles[i].obj == OBJ_NONE) continue;
		_tiles[i].objImg->frameRender(
			screen.left + 830 + (_tiles[i].rc.left / (TILESIZE / 3)), 
			screen.top - 130 + (TILESIZE * 3) + (_tiles[i].rc.top / (TILESIZE / 3)),
			_tiles[i].objFrameX, _tiles[i].objFrameY, MINITILESIZE, MINITILESIZE);
	}
}

void tileManager::load(const char* mapName, int width, int height)
{
	HANDLE file;
	DWORD read;
	_width = width;
	_height = height;

	file = CreateFile(mapName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * _width * _height, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) *  _width * _height);
	

	for (int i = 0; i < _width*_height; ++i)
	{
		_tiles[i].terrainFrameX;
		_tiles[i].terrainFrameY;
		_tiles[i].objFrameX;
		_tiles[i].objFrameY;
		_tiles[i].terrain;
		_tiles[i].obj;
		_tiles[i].z;
		_tiles[i].objImg = _mapTile[_tiles[i].objImgIndex];

		_loadTiles[i] = _tiles[i];
	}

	CloseHandle(file);
}