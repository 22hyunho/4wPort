#include "stdafx.h"
#include "mapToolScene.h"
HRESULT mapToolScene::init(Player* player)
{
	Scene::init(player);

	_maptool = new Maptool;
	_maptool->init();
	_width = _maptool->getWidth();
	_height = _maptool->getHeight();

	CAMERAMANAGER->setBackScreenSize(TILESIZE * _width, TILESIZE * _height);
	
	x = 0;
	y = 0;
	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	_maptool->update();
	if (KEYMANAGER->isStayKeyDown('W'))y-=50;
	if (KEYMANAGER->isStayKeyDown('A'))x-=50;
	if (KEYMANAGER->isStayKeyDown('S'))y+=50;
	if (KEYMANAGER->isStayKeyDown('D'))x+=50;
	
	if (x < 0)x = 0;
	if (y < 0)y = 0;
	if (x > TILESIZE * _width)x = TILESIZE * _width;
	if (y > TILESIZE * _height)y = TILESIZE *_height;
	CAMERAMANAGER->updateScreen(x, y);
}

void mapToolScene::render()
{
	//D2D1_RECT_F rc = CAMERAMANAGER->getScreen();
	
	_maptool->render();
	//if (PRINTMANAGER->isDebug())
	//{
	WCHAR str[128];
	swprintf_s(str, L"_width: %d, _height: %d", _ptMouse.x / TILESIZE, _ptMouse.y / TILESIZE);
	DTDMANAGER->printText(str, _ptMouse.x, _ptMouse.y, 150, 0);
	//swprintf_s(str, L"x: %d, y: %d, type: %d", _ptMouse.x, _ptMouse.y,_maptool->getType());
	//DTDMANAGER->printText(str, _ptMouse.x, _ptMouse.y, 150, 200);
	//_maptool->minimap();
	//}

}

void mapToolScene::changeScene()
{
}
