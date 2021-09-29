#include "stdafx.h"
#include "Transform.h"

HRESULT Transform::init(float x, float y, bool reverse)
{
	Effect::init(x, y, reverse);
	_img = IMAGEMANAGER->addFrameDImage("transform", L"img/boss/halfElf_transform.png", 1080, 180, 8, 1);
	if (!_reverse)
	{
		_frameX = 0;
		_frameY = 0;
	}
	else
	{
		_frameX = _img->getMaxFrameX();
		_frameY = 0;
	}
	_rc = RectMakeCenter(_x, _y, TILESIZE * 3, TILESIZE * 3);

	_type = EF_NONATTACK;

	return S_OK;
}

void Transform::release()
{
}

void Transform::update()
{
}

void Transform::render()
{
	_img->frameRender(_rc.left, _rc.top, _frameX, 0);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_rc);

	controlFrame();
}

void Transform::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();
	if (!_reverse)
	{
		if (_count >= 0.1)
		{
			if (_frameX >= _img->getMaxFrameX())
			{
				_frameX = _img->getMaxFrameX();

				_off = true;
			}

			else
				_frameX++;

			_count = 0;
		}
	}
	else
	{
		if (_count >= 0.1)
		{
			if (_frameX <= 0)
			{
				_frameX = 0;

				_offCount++;
				if (_offCount >= 23)
				{
					_off = true;
					_offCount = 0;
				}
			}

			else
				_frameX--;

			_count = 0;
		}
	}
}
