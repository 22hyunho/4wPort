#include "stdafx.h"
#include "Artifact.h"

HRESULT Artifact::init(float x, float y)
{
	_x = x;
	_y = y;
	return S_OK;
}
