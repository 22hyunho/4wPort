#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		SCENEMANAGER->init();
		TIMEMANAGER->init();
		PRINTMANAGER->init();
		STREAMMANAGER->init();
		DTDMANAGER->init();
		CAMERAMANAGER->init();
		TXTDATA->init();
		TILEMANAGER->init();
		EFFECTMANAGER->init();
		ITEMMANAGER->init();
		ARTIFACTDEX->init();
		FOODDEX->init();
		SOUNDMANAGER->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		PRINTMANAGER->release();
		PRINTMANAGER->releaseSingleton();

		STREAMMANAGER->release();
		STREAMMANAGER->releaseSingleton();

		DTDMANAGER->release();
		DTDMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		TILEMANAGER->release();
		TILEMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		ITEMMANAGER->release();
		ITEMMANAGER->releaseSingleton();

		ARTIFACTDEX->release();
		ARTIFACTDEX->releaseSingleton();

		FOODDEX->release();
		FOODDEX->releaseSingleton();

		INVENTORY->release();
		INVENTORY->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		PLAYERUI->release();
		PLAYERUI->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		CoUninitialize();
	}
}

void gameNode::update()
{
}

void gameNode::render()
{
}

void gameNode::cursorOnWindow()
{
	RECT rc;
	//扩档快 农扁 RECT 积己
	GetClientRect(_hWnd, &rc);

	POINT pt1, pt2;

	//扩档快 LeftTop, RightTop痢 谅钎
	pt1.x = rc.left;
	pt1.y = rc.top;
	pt2.x = rc.right;
	pt2.y = rc.bottom;

	//函券
	ClientToScreen(_hWnd, &pt1);
	ClientToScreen(_hWnd, &pt2);

	//措涝
	rc.left = pt1.x;
	rc.top = pt1.y;
	rc.right = pt2.x;
	rc.bottom = pt2.y;

	//付快胶 绊沥
	ClipCursor(&rc);
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
		//PAINTSTRUCT ps;
		//HDC         hdc; //娟 吗 吝夸钦聪...
	D2D1_RECT_F _rc = CAMERAMANAGER->getScreen();

	switch (iMessage)
	{
		//付快胶 框流捞搁 咯扁辑 皋技瘤 惯积
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam)) + _rc.left;
		_ptMouse.y = static_cast<float>(HIWORD(lParam)) + _rc.top;


		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_ACTIVATEAPP:
		//cursorOnWindow();
		break;

		//扩档快 芒 何浆绰(?) 
	case WM_DESTROY:
		//扩档快 辆丰窃荐
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}