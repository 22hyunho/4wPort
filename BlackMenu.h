#pragma once
#include "UpMenu.h"

class BlackMenu : public UpMenu
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

