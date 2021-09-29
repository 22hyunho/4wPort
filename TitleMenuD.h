#pragma once
#include "DownMenu.h"

enum TITLEMENU_OPTION {
	TITLEMENU_OPTION_NEW,
	TITLEMENU_OPTION_CONTINUE,
	END_TITLEMENU_OPTION
};

class TitleMenuD : public DownMenu
{
private:
	int _maxIndex;

	bool _opacity;
	int _count;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void checkSave();
};

