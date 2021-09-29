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
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();			//�׸��� �Լ�

	Artifact* registerArtifact(int num, Artifact* artifact);

	HRESULT makeArtifact(float x, float y, int num);
	void removeArtifact(int num);
	void clearArtifact();

	vArtifact getVArtifact() { return _vArtifact; }			//�� ������ ��Ƽ��Ʈ
	viArtifact getVIArtifact() { return _viArtifact; }
};

