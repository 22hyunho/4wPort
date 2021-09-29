#pragma once
#include "KeyNDirect.h"

#define DOWNMENU_WIDTH	687
#define DOWNMENU_HEIGHT	562

class DownMenu
{
protected:
	dImage* _back;
	dImage* _border;
	dImage* _arrow;

	float _tuningX;
	float _tuningY;

	int _index;
	bool _hidden;

public:
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render();	

	bool getHidden() { return _hidden; }
	void setHidden(bool hidden) { _hidden = hidden; }
};