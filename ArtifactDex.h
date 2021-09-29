#pragma once
#include "singletonBase.h"
#include "Artifact.h"

class ArtifactDex : public singletonBase<ArtifactDex>
{
private:
	typedef map<int, Artifact*>				artifactList;
	typedef map<int, Artifact*>::iterator	artifactIter;

	typedef vector<Artifact*>				vArtifact;
	typedef vector<Artifact*>::iterator		viArtifact;

private:
	artifactList _mArtifact;
	artifactIter _miArtifact;

	vArtifact	 _vArtifact;
	viArtifact	 _viArtifact;

public:
	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();			//그리기 함수

	Artifact* registerArtifact(int num, Artifact* artifact);

	HRESULT makeArtifact(float x, float y, int num);
	void removeArtifact(int num);
	void clearArtifact();

	vArtifact getVArtifact() { return _vArtifact; }			//맵 생성용 아티팩트
	viArtifact getVIArtifact() { return _viArtifact; }
};

