#pragma once

#include "targetver.h"
#include "resource.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

//d2d lib
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "WindowsCodecs.lib")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include "Resource.h"
#include "macroFunc.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "cameraManager.h"
#include "timeManager.h"
#include "sceneManager.h"
#include "printManager.h"
#include "collisionManager.h"
#include "tileManager.h"
#include "effectManager.h"
#include "itemManager.h"
#include "ArtifactDex.h"
#include "FoodDex.h"
#include "Inventory.h"
#include "uiManager.h"
#include "playerUI.h"
#include "txtData.h"
#include "streamManager.h"
#include "dtdManager.h"
#include "soundManager.h"


using namespace std;
using namespace MACRO_FUNC;
using namespace D2D1;

//==================================
// ## 매크로 처리 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("Mana Spark"))
#define WINSTARTX 0	//윈도우 창 시작좌표 (left)
#define WINSTARTY 0	//윈도우 창 시작좌표 (top)
#define WINSIZEX 1000	//윈도우 가로크기
#define WINSIZEY 800	//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define PRINTMANAGER printManager::getSingleton()
#define COLLISIONMANAGER collisionManager::getSingleton()
#define TILEMANAGER tileManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define ITEMMANAGER itemManager::getSingleton()
#define ARTIFACTDEX ArtifactDex::getSingleton()
#define FOODDEX FoodDex::getSingleton()
#define INVENTORY Inventory::getSingleton()
#define UIMANAGER uiManager::getSingleton()
#define PLAYERUI playerUI::getSingleton()
#define TXTDATA txtData::getSingleton()
#define STREAMMANAGER streamManager::getSingleton()
#define DTDMANAGER dtdManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()

#define SAFE_DELETE(p) { if(p) { delete(p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p); (p) = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->release(); (p) = NULL; } }
#define SAFE_RELEASE2(p) { if(p) { (p)->Release(); (p) = NULL; } }

#define TILEWIDTH	48
#define TILEHEIGHT	48

//==================================
// ## extern ##
//==================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;