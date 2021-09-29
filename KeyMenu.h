#pragma once
#include "UpMenu.h"

class KeyMenu : public UpMenu
{
private:

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

