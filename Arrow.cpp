#include "stdafx.h"
#include "Arrow.h"

void Arrow::update()
{
	COLLISIONMANAGER->collisionArrow(this);
}
