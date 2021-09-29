#pragma once
#include "DownMenu.h"

class LogMenu : public DownMenu
{
private:
	typedef vector<wstring>				logList;
	typedef vector<wstring>::iterator	logIter;

private:
	logList* _logList;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

