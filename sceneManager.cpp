#include "stdafx.h"
#include "sceneManager.h"
#include "Scene.h"

#include "SceneHeader.h"

Player* sceneManager::_player = NULL;
Scene* sceneManager::_currentScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::init()
{
	SCENEMANAGER->addScene("maptool", new mapToolScene);
	SCENEMANAGER->addScene("town", new town);
	SCENEMANAGER->addScene("mystery", new mysteryRoom);
	SCENEMANAGER->addScene("forest1", new forest1);
	SCENEMANAGER->addScene("brick1", new brick1);
	SCENEMANAGER->addScene("crypt1", new crypt1);
	SCENEMANAGER->addScene("boss1", new bossRoom1);
	SCENEMANAGER->addScene("boss2", new bossRoom2);
	SCENEMANAGER->addScene("intro", new introScene);
	SCENEMANAGER->addScene("title", new titleScene);
	SCENEMANAGER->addScene("end", new endScene);
	SCENEMANAGER->addScene("gameOver", new gameOverScene);

	return S_OK;
}

HRESULT sceneManager::init(Player * player)
{
	_player = player;

	return S_OK;
}

//��
void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{					//���̶� �ʿ��� second
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

Scene* sceneManager::addScene(string sceneName, Scene* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init(_player)))
	{
		//����(�ִ�) ���� ������ �Լ��� �������ְ�
		if (_currentScene) _currentScene->release();

		//�ٲٷ��� ���� ��������� ü����
		_currentScene = find->second;

		CAMERAMANAGER->setFade(FADEIN);

		return S_OK;
	}

	return E_FAIL;
}