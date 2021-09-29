#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	//backDC와 frontDC크기 설정
	_backWidth = WINSIZEX;
	_backHeight = WINSIZEY;
	_frontWidth = WINSIZEX;
	_frontHeight = WINSIZEY;

	//화면 Rect 생성
	_screen = dRectMake(0, 0, WINSIZEX, WINSIZEY);

	//fade화면
	_fadeScreen = IMAGEMANAGER->addDImage("fade_B", L"img/fade_B.png", WINSIZEX , WINSIZEY);

	_alpha = 1.0;
	_fade = NORMAL;

	//설정값
	_count = 0;
	_ratioX = 0.5;
	_ratioY = 0.5;
	_camY = 0;
	_onMove = false;

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::updateScreen(float standardX, float standardY)
{
	//플레이어 기준으로 화면(_screen)갱신
	//playground.cpp의 update()에서 계속 갱신해주면 됨
	//인수로 기준이 되는 객체의 x, y좌표를 받음(현재는 player의 x, y)

	if (!_onMove)
		resetCam();

	float x = standardX;
	float y = standardY;

	onWindow(x, y);
	//갱신
	_screen = dRectMake(x, y, _frontWidth, _frontHeight);
}

void cameraManager::moveCam(int direct)
{
	_onMove = true;

	switch (direct) {
	case 2:	//UP
		_camY = _camY - 10 > -240 ? _camY - 10 : -240;
		break;
	case 3:	//DOWN
		_camY = _camY + 10 < 240 ? _camY + 10 : 240;
		break;
	default:
		break;
	}
}

void cameraManager::resetCam()
{
	if (_camY > 0)
		_camY = _camY - 40 > 0 ? _camY - 40 : 0;
	else if (_camY < 0)
		_camY = _camY + 40 < 0 ? _camY + 40 : 0;
}

void cameraManager::fade()
{
	//페이드 인 아웃
	if (_fade == FADEIN)		fadeIn();
	else if (_fade == FADEOUT)	fadeOut();
}

void cameraManager::fadeIn()
{
	_alpha -= FADE * TIMEMANAGER->getElapsedTime() * 0.7f;
	if (_alpha < 0) _alpha = 0;

	if (_alpha == 0) _fade = NORMAL;

	D2D1_RECT_F dest = dRectMake(0, 0, _frontWidth, _frontHeight);
	D2D1_RECT_F sour = dRectMake(0, 0, _fadeScreen->getWidth(), _fadeScreen->getHeight());
	DTDMANAGER->getRenderTarget()->DrawBitmap(_fadeScreen->getBitmap(), dest,
		_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sour);
}

void cameraManager::fadeOut()
{
	_alpha += FADE * TIMEMANAGER->getElapsedTime() * 0.7f;
	if (_alpha > 1.0) _alpha = 1.0;

	if (_alpha == 1.0) _fade = NORMAL;

	D2D1_RECT_F dest = dRectMake(0, 0, _frontWidth, _frontHeight);
	D2D1_RECT_F sour = dRectMake(0, 0, _fadeScreen->getWidth(), _fadeScreen->getHeight());
	DTDMANAGER->getRenderTarget()->DrawBitmap(_fadeScreen->getBitmap(), dest,
		_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sour);
}

void cameraManager::vibrateScreen(float standardX, float standardY, float magnitude, float interval)
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= interval) {
		updateScreen(standardX + RND->getFromFloatTo(-magnitude, magnitude),
			standardY + RND->getFromFloatTo(-magnitude, magnitude));
		_count = 0;
	}
}

void cameraManager::vibrateScreenOut(float standardX, float standardY, float magnitude, float interval)
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= interval) {
		float x = standardX;
		float y = standardY + _camY;

		onWindow(x, y);
		_screen = dRectMake(x + RND->getFromFloatTo(-magnitude, magnitude),
			y + RND->getFromFloatTo(-magnitude, magnitude),
			_frontWidth, _frontHeight);
		_count = 0;
	}
}

void cameraManager::render(float destX, float destY)
{
	/********* 인수 설명 *********/ /*
	int destX: 우리가 보는 화면에서 출력해줄 x좌표
	int destY: 우리가 보는 화면에서 출력해줄 y좌표
	*/

	DTDMANAGER->render(destX, destY, _frontWidth, _frontHeight);

#ifdef _DEBUG
#endif // _DEBUG

}

void cameraManager::onWindow(float & x, float & y)
{
	//X축 (좌, 우)
	if (x - _frontWidth * _ratioX < 0)
		x = 0;
	else if (x + _frontWidth * (1 - _ratioX) > _backWidth)
		x = _backWidth - _frontWidth;
	else
		x -= _frontWidth * _ratioX;
	//Y축 (상, 하)
	if (y - _frontHeight * _ratioY < 0)
		y = 0;
	else if (y + _frontHeight * (1 - _ratioY) > _backHeight)
		y = _backHeight - _frontHeight;
	else
		y -= _frontHeight * _ratioY;
}

void cameraManager::setBackScreenSize(float width, float height)
{
	_backWidth = width, _backHeight = height;

	DTDMANAGER->setBackBuffer(width, height);
}
