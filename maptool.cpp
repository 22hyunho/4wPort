#include "stdafx.h"
#include "maptool.h"


HRESULT Maptool::init()
{
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

	_width = 40;	//가로세로 타일갯수
	_height = 60;
	_saveDate = "boss1.map";

	mode = true;
	_tool = false;
	setup();

	return S_OK;
}

void Maptool::release()
{
}

void Maptool::update()
{
	//키 누를때만 setmap 하게
	setMap();
	if (KEYMANAGER->isOnceKeyDown('Z')) _tool = !_tool;
	setTool();
	imageClipping();

	if (KEYMANAGER->isStayKeyDown('W')) _minimapY -= 1;
	if (KEYMANAGER->isStayKeyDown('A')) _minimapX -= 1;
	if (KEYMANAGER->isStayKeyDown('S')) _minimapY += 1;
	if (KEYMANAGER->isStayKeyDown('D')) _minimapX += 1;

	if (KEYMANAGER->isOnceKeyDown('X') && _tool)
	{
		_type--;
		if (_type < 0) _type = 12;
	}
	if (KEYMANAGER->isOnceKeyDown('C') && _tool)
	{
		_type++;
		if (_type > 12) _type = 0;
	}
}

void Maptool::render()
{
	//====================================== 정해진 범위의 타일만 render ======================================
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
			if (_tiles[index].objImg != nullptr);

			_tiles[index].objImg->frameRender(_tiles[index].rc.left, _tiles[index].rc.top,
				_tiles[index].objFrameX, _tiles[index].objFrameY);
		}
	//========================================================================================================
	

	if (PRINTMANAGER->isDebug())
	{
		minimap();
	}

	if (_tool)
	{
		_mapTile[_type]->render(_toolRC.left, _toolRC.top);			//샘플용 타일 렌더
		RECT border = RectMake(_toolRC.left, _toolRC.top, TILESIZE * SAMPLETILEX, TILESIZE * SAMPLETILEY);
		DTDMANAGER->Rectangle(border);
		for (int i = 0; i < 2; i++)
		{
			DTDMANAGER->Rectangle(_saveLoad[i]);
		}
		for (int i = 0; i < 4; i++)
		{
			DTDMANAGER->Rectangle(_terrainRC[i]);
			DTDMANAGER->Rectangle(_zOrder[i]);
		}
		if (_ctrSelect <= CTRL_OBJDRAW)
		{
			for (int i = 0; i < 7; i++)
			{
				DTDMANAGER->Rectangle(_attr[i]);
			}
		}

		DTDMANAGER->printText(L"TERRAIN", _terrainRC[0].left + 55, _terrainRC[0].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"OBJECT", _terrainRC[1].left + 55, _terrainRC[1].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"ERASE", _terrainRC[2].left + 55, _terrainRC[2].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"NULL", _terrainRC[3].left + 55, _terrainRC[3].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"SAVE", _saveLoad[0].left + 55, _saveLoad[0].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"LOAD", _saveLoad[1].left + 55, _saveLoad[1].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"Z0", _zOrder[0].left + 55, _zOrder[1].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"Z1", _zOrder[1].left + 55, _zOrder[1].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"Z2", _zOrder[2].left + 55, _zOrder[1].top + 20, 100, 20, 20);
		DTDMANAGER->printText(L"Z3", _zOrder[3].left + 55, _zOrder[1].top + 20, 100, 20, 20);

		if (_ctrSelect == CTRL_TERRAINDRAW)
		{
			DTDMANAGER->printText(L"BLOCK", _attr[0].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"WATER", _attr[1].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"POISON", _attr[2].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"GRASS", _attr[3].left + 55, _attr[0].top + 20, 100, 20, 20);
		}
		else if (_ctrSelect == CTRL_OBJDRAW)
		{
			DTDMANAGER->printText(L"BLOCK", _attr[0].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"TRAP1", _attr[1].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"TRAP2", _attr[2].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"STAIR", _attr[3].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"LEVER", _attr[4].left + 55, _attr[0].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"NONE", _attr[5].left + 55, _attr[5].top + 20, 100, 20, 20);
			DTDMANAGER->printText(L"NORMAL", _attr[6].left + 55, _attr[6].top + 20, 100, 20, 20);
		}
		D2D1_RECT_F info = dRectMake(_toolRC.left, _toolRC.top - 130, 130, 20);
		WCHAR str[128];
		swprintf_s(str, L"ter or obj : %d ", _ctrSelect);
		DTDMANAGER->printText(str, info, 20);
		info.top += 30;
		info.bottom += 30;
		swprintf_s(str, L"Z Order	 : %d ", _ctrZ);
		DTDMANAGER->printText(str, info, 20);
		info.top += 30;
		info.bottom += 30;
		swprintf_s(str, L"sIndexX	 : %d ", _selectIndexX[0]);
		DTDMANAGER->printText(str, info, 20);
		info.top += 30;
		info.bottom += 30;
		swprintf_s(str, L"sIndexY	 : %d ", _selectIndexY[0]);
		DTDMANAGER->printText(str, info, 20);
		info = dRectMake(_toolRC.left + 150, _toolRC.top - 130, 130, 20);
		swprintf_s(str, L"TerAtt	 : %d ", _ctrTerAtt);
		DTDMANAGER->printText(str, info, 20);
		info.top += 30;
		info.bottom += 30;
		swprintf_s(str, L"TerObj	 : %d ", _ctrObjAtt);
		DTDMANAGER->printText(str, info, 20);

		RECT rc;
		rc = RectMake(_sampleTile[_selectIndexY[0] * SAMPLETILEX + _selectIndexX[0]].rc.left,
			_sampleTile[_selectIndexY[0] * SAMPLETILEX + _selectIndexX[0]].rc.top,
			(_selectIndexX[1] + 1 - _selectIndexX[0]) * TILESIZE,
			(_selectIndexY[1] + 1 - _selectIndexY[0]) * TILESIZE);
		DTDMANAGER->Rectangle(rc);
	}

	if (PtInRect(&_allMapRC, _ptMouse) && !_tool)
	{
		RECT drawRect;
		drawRect = RectMake(															//드로우 렉트
			_tiles[_mouseY * _width + _mouseX].rc.left,
			_tiles[_mouseY * _width + _mouseX].rc.top,
			TILESIZE + TILESIZE * (_selectIndexX[1] - _selectIndexX[0]),
			TILESIZE + TILESIZE * (_selectIndexY[1] - _selectIndexY[0]));
		DTDMANAGER->Rectangle(drawRect);
	}
}

void Maptool::save(const char * mapName)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(mapName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * _width * _height, &write, NULL);
	CloseHandle(file);
}

void Maptool::load(const char * mapName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(mapName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * _width * _height, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) *  _width * _height);
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			SetRect(&_tiles[i * _width + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

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
	}

	CloseHandle(file);
}

void Maptool::setup()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_allMapRC = RectMake(0, 0, _width * TILESIZE, _height * TILESIZE);

	_ctrSelect = CTRL_TERRAINDRAW;
	_ctrZ = 0;
	_ctrTerAtt = TR_GRASS;
	_ctrObjAtt = OBJ_NONE;
	_terOrObj = 0;
	_type = 0;
	_selectIndexX[0] = 0;
	_selectIndexY[0] = 0;
	_selectIndexX[1] = 0;
	_selectIndexY[1] = 0;
	//타일 영역
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			SetRect(&_tiles[i * _width + j].rc,
				j * TILESIZE,				//x 레프트
				i * TILESIZE,				//y 탑
				j * TILESIZE + TILESIZE,	//x 라이트
				i * TILESIZE + TILESIZE);	//y 바텀
		}
	}

	for (int i = 0; i < _width * _height; ++i)
	{
		_tiles[i].terImgIndex = 0;
		_tiles[i].objImgIndex = 0;
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = _ctrTerAtt;
		_tiles[i].obj = _ctrObjAtt;
		//_tiles[i].x = _tiles[i].rc.left + _tiles[i].rc.right / 2;
		//_tiles[i].y = _tiles[i].rc.top + _tiles[i].rc.bottom / 2;
		_tiles[i].z = 0;
	}
}

void Maptool::setSample()
{
	//타일셋 세팅

	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//타일셋에 렉트를 씌움
			SetRect(&_sampleTile[i * SAMPLETILEX + j].rc,
				_toolRC.left + j * TILESIZE,										//x 레프트
				_toolRC.top + i * TILESIZE,																		//y 탑
				_toolRC.left + j * TILESIZE + TILESIZE,		//x 라이트
				_toolRC.top + i * TILESIZE + TILESIZE);																//y 바텀
		}
	}
}

void Maptool::setMap()
{
	if (PtInRect(&_allMapRC, _ptMouse) && !_tool)
	{
		_mouseX = _ptMouse.x / TILESIZE;
		_mouseY = _ptMouse.y / TILESIZE;
	}
	if (PtInRect(&_toolRC, _ptMouse) && _tool)
	{
		_mouseX = (_ptMouse.x - _toolRC.left) / TILESIZE;
		_mouseY = (_ptMouse.y - _toolRC.top) / TILESIZE;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		{
			if (PtInRect(&_toolRC, _ptMouse) && _tool)		//지형 관련 도구
			{
				_selectIndexX[0] = _mouseX;
				_selectIndexY[0] = _mouseY;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_terrainRC[i], _ptMouse) && _tool)				//타일 그리기 도구
			{
				switch (i)
				{
				case 0:
					_ctrSelect = CTRL_TERRAINDRAW;
					_ctrTerAtt = TR_GRASS;
					_ctrObjAtt = OBJ_NONE;
					_ctrZ = 0;
					break;

				case 1:
					_ctrSelect = CTRL_OBJDRAW;
					_ctrObjAtt = OBJ_BLOCK;
					_ctrTerAtt = TR_BLOCK;
					_ctrZ = 1;
					break;

				case 2:
					_ctrSelect = CTRL_ERASER;
					break;

				case 3:
					allTileBase();
					break;
				}
			}

			if (PtInRect(&_saveLoad[i], _ptMouse) && _tool)					//세이브 & 로드
			{
				switch (i)
				{
				case 0:
					save(_saveDate);
					break;

				case 1:
					load(_saveDate);
					break;
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_zOrder[i], _ptMouse) && _tool)					// Z오더
			{
				switch (i)
				{
				case 0:
					_ctrZ = 0;
					break;

				case 1:
					_ctrZ = 1;
					break;

				case 2:
					_ctrZ = 2;
					break;

				case 3:
					_ctrZ = 3;
					break;
				}
			}
		}
		for (int i = 0; i < 7; i++)											// 타일 속성 넣기
		{
			if (PtInRect(&_attr[i], _ptMouse) && _tool && _ctrSelect == CTRL_TERRAINDRAW)
			{
				switch (i)
				{
				case 0 : 
					_ctrTerAtt = TR_BLOCK;
					break;

				case 1 :
					_ctrTerAtt = TR_WATER;
					break;

				case 2 :
					_ctrTerAtt = TR_POISON;
					break;

				case 3 :
					_ctrTerAtt = TR_GRASS;
					break;

				case 4 :
					break;

				case 5 :
					break;

				case 6 :
					break;
				}
			}
			else if (PtInRect(&_attr[i], _ptMouse) && _tool && _ctrSelect == CTRL_OBJDRAW)
			{
				switch (i)
				{
				case 0 :
					_ctrObjAtt = OBJ_BLOCK;
					break;

				case 1 :
					_ctrObjAtt = OBJ_TRAP1;
					break;

				case 2 :
					_ctrObjAtt = OBJ_TRAP2;
					break;

				case 3 :
					_ctrObjAtt = OBJ_STAIR;
					break;

				case 4 :
					_ctrObjAtt = OBJ_LEVER;
					break;

				case 5 :
					_ctrObjAtt = OBJ_NONE;
					break;

				case 6 :
					_ctrObjAtt = OBJ_NORMAL;
					break;
				}
			}
		}
	}

	

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))								// 맵에 지정한 지형 그리기
	{
		if (PtInRect(&_allMapRC, _ptMouse) && !_tool)
		{
			for (int i = 0; i <= _selectIndexX[1] - _selectIndexX[0]; ++i)
			{
				for (int j = 0; j <= _selectIndexY[1] - _selectIndexY[0]; ++j)
				{
					if (_ctrSelect == CTRL_TERRAINDRAW)
					{
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].terrainFrameX = _selectIndexX[0] + i;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].terrainFrameY = _selectIndexY[0] + j;

						_tiles[(_mouseY + j) * _width + (_mouseX + i)].terrain = _ctrTerAtt;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].terImgIndex = _type;
					}
					else if (_ctrSelect == CTRL_OBJDRAW)
					{
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objImg = _mapTile[_type];
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objImgIndex = _type;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objFrameX = _selectIndexX[0] + i;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objFrameY = _selectIndexY[0] + j;

						_tiles[(_mouseY + j) * _width + (_mouseX + i)].obj = _ctrObjAtt;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].z = _ctrZ;
					}
					else if (_ctrSelect == CTRL_ERASER)
					{
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objImg = nullptr;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objFrameX = NULL;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].objFrameY = NULL;
						_tiles[(_mouseY + j) * _width + (_mouseX + i)].obj = OBJ_NONE;
					}
					//InvalidateRect(_hWnd, NULL, false);
				}
			}
		}
		

		if (PtInRect(&_toolRC, _ptMouse) && _tool)
		{
			_selectIndexX[1] = _mouseX;
			_selectIndexY[1] = _mouseY;
		}
	}
}

void Maptool::setTool()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_toolRC = RectMake(screen.left + WINSIZEX / 3 - 96, screen.top + WINSIZEY / 5,
		TILEWIDTH * 12, TILEHEIGHT * 6);

	_terrainRC[0] = RectMake(_toolRC.left, _toolRC.bottom + 30, 100, 50);
	_terrainRC[1] = RectMake(_terrainRC[0].right + 30, _terrainRC[0].top, 100, 50);
	_terrainRC[2] = RectMake(_terrainRC[1].right + 30, _terrainRC[0].top, 100, 50);
	_terrainRC[3] = RectMake(_terrainRC[2].right + 30, _terrainRC[0].top, 100, 50);
	_saveLoad[0] = RectMake(_terrainRC[3].right + 30, _terrainRC[0].top, 100, 50);
	_zOrder[0] = RectMake(_terrainRC[0].left, _terrainRC[0].bottom + 30, 100, 50);
	_zOrder[1] = RectMake(_zOrder[0].right + 30, _terrainRC[0].bottom + 30, 100, 50);
	_zOrder[2] = RectMake(_zOrder[1].right + 30, _terrainRC[0].bottom + 30, 100, 50);
	_zOrder[3] = RectMake(_zOrder[2].right + 30, _terrainRC[0].bottom + 30, 100, 50);
	_saveLoad[1] = RectMake(_zOrder[3].right + 30, _terrainRC[0].bottom + 30, 100, 50);
	_attr[0] = RectMake(_zOrder[0].left, _zOrder[0].bottom + 30, 100, 50);
	_attr[1] = RectMake(_attr[0].right + 30, _zOrder[0].bottom + 30, 100, 50);
	_attr[2] = RectMake(_attr[1].right + 30, _zOrder[0].bottom + 30, 100, 50);
	_attr[3] = RectMake(_attr[2].right + 30, _zOrder[0].bottom + 30, 100, 50);
	_attr[4] = RectMake(_attr[3].right + 30, _zOrder[0].bottom + 30, 100, 50);
	_attr[5] = RectMake(_attr[0].left, _attr[0].bottom + 30, 100, 50);
	_attr[6] = RectMake(_attr[1].left, _attr[0].bottom + 30, 100, 50);

	setSample();
}

void Maptool::minimap()
{
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

	for (int i = 0; i < _width * _height; ++i)
	{
		_mapTile[_tiles[i].terImgIndex]->frameRender(
			screen.left + (_tiles[i].rc.left / (TILESIZE / 3)), screen.top + (TILESIZE * 3) + (_tiles[i].rc.top / (TILESIZE / 3)),
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY, MINITILESIZE, MINITILESIZE);

		if (_tiles[i].obj == OBJ_NONE) continue;
		_tiles[i].objImg->frameRender(
			screen.left + (_tiles[i].rc.left / (TILESIZE / 3)), screen.top + (TILESIZE * 3) + (_tiles[i].rc.top / (TILESIZE / 3)),
			_tiles[i].objFrameX, _tiles[i].objFrameY, MINITILESIZE, MINITILESIZE);
	}
}

void Maptool::imageClipping()
{
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

void Maptool::allTileBase()
{
	for (int i = 0; i < _height * _width; i++)
	{
		_tiles[i].terImgIndex = _type;
		_tiles[i].objImgIndex = 0;
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].terrain = TR_GRASS;
		_tiles[i].objFrameX = NULL;
		_tiles[i].objFrameY = NULL;
		_tiles[i].obj = OBJ_NONE;
		_tiles[i].z = 0;
	}
}

TERRAIN Maptool::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 3; j < 15; j++)
		{
			if (frameX == j && frameY == i)
			{
				return TR_BLOCK;
			}
		}
	}

	return TR_GRASS;
}

OBJECT Maptool::objSelect(int frameX, int frameY)
{
	if ((frameX == 0 && frameY == 0) &&
		(frameX == 1 && frameY == 3) &&
		(frameX == 2 && frameY == 6) &&
		(frameX == 3 && frameY == 9) &&
		(frameX == 0 && frameY == 0) &&
		(frameX == 0 && frameY == 3) &&
		(frameX == 15 && frameY == 6) &&
		(frameX == 15 && frameY == 9))
	{
		return OBJ_BLOCK;
	}
	else

		return OBJ_BLOCK;
}
