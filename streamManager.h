#pragma once
#include "singletonBase.h"
#include "video.h"
#include <map>

class streamManager : public singletonBase<streamManager>
{
private:
	typedef map<string, video*>				mapVideoList;
	typedef map<string, video*>::iterator	mapVideoIter;

	mapVideoList _mapVideoList;
	video* _currentVideo;
	video* _currentVideo2;

public:
	streamManager();
	~streamManager();
	HRESULT init();
	void release();

	video* addVideo(string strKey, const char* fileName);
	void startVideo(string strKey);
	void startVideo(string strKey, D2D1_RECT_F rc);
	void startVideo2(string strKey, D2D1_RECT_F rc);
	void closeVideo();
	void closeVideo2();

	//void getPosition();
	//void getLenthEnd();

	video* findVideo(string strKey);

	BOOL deleteAll();

	long getPosition() { return _currentVideo->getPosition(); }
	long getLength() { return _currentVideo->getLength(); }
	video* getCurrentVideo() { return _currentVideo; }
};