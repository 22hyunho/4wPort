#include "stdafx.h"
#include "dialogManager.h"
#include "Item.h"

HRESULT dialogManager::init()
{
	_back = IMAGEMANAGER->addDImage("dialog_back", L"img/ui/dialog/back.png", 687, 562);
	_border = IMAGEMANAGER->addDImage("dialog_border", L"img/ui/dialog/border.png", 687, 562);
	_leftBorder = IMAGEMANAGER->addDImage("dialog_left_border", L"img/ui/dialog/left_border.png", 687, 562);
	_rightBorder = IMAGEMANAGER->addDImage("dialog_right_border", L"img/ui/dialog/right_border.png", 687, 562);

	_currentFileName = NULL;

	_size = 0;
	_count = 0;

	_print = false;

	return S_OK;
}

void dialogManager::release()
{
	//battleLog 초기화
	battleIter iter = _battleLog.begin();

	for (; iter != _battleLog.end();)
		iter = _battleLog.erase(iter);

	_battleLog.clear();
}

void dialogManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(KEY_A)) {
		if (_size >= 128) {
			//다음으로
			loadScript();

			_size = 0;
		}
		else
			_size = 128;
	}
}

void dialogManager::render()
{
	//문자크기 조절
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.1) {
		if (_size < 128)
			_size++;
		_count = 0;
	}


	//화면기준으로 render
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_back->render(screen.left, screen.top);
	_border->render(screen.left, screen.top);


	//포켓몬 정보 가져오기
	int pokeNum = _wtoi(_storyMetaData[_metaDataNum]);
	Pokemon* pokemon;
	switch (pokeNum) {
	case 0:		//player
		pokemon = (*TURNMANAGER->getAllPlayer())[0]->getPokemon();
		break;
	case -5:	//NONE
		pokemon = nullptr;
		break;
	default:
		pokemon = POKEDEX->makePokemon(pokeNum);
		pokemon->init();
		break;
	}


	//초상화 출력
	if (!wcscmp(_storyMetaData[_metaDataNum + 1], L"LEFT")) {
		//왼쪽에 초상화
		pokemon->getPortrait()->render(screen.left + 100, screen.top + 125, 0, 0, 120, 120);
		_leftBorder->render(screen.left, screen.top + 25);
	}
	else if (!wcscmp(_storyMetaData[_metaDataNum + 1], L"RIGHT")) {
		//오른쪽에 초상화
		DTDMANAGER->setReverse(0, (screen.right - 220) * 2 + 120, 0);
		pokemon->getPortrait()->render(screen.right - 220, screen.top + 125, 0, 0, 120, 120);
		_rightBorder->render(screen.left, screen.top + 25);
		DTDMANAGER->resetTransform();
	}
	else {
		//초상화 없음
	}


	//텍스트 불러오기
	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", _scriptNum);
	WCHAR text[128];
	if (pokemon)
		swprintf_s(text, L"%s: ", pokemon->getName().c_str());
	else
		swprintf_s(text, L"");
	lstrcatW(text, TXTDATA->loadDataString(_currentFileName,
		&_storyMetaData[_metaDataNum][0], tmp, _size));


	//인스턴스 해제
	if (pokeNum > 0)
		SAFE_DELETE(pokemon);


	//출력위치 조정
	DTDMANAGER->printText(text, screen.left + 344, screen.top + 374, 490, 120, 30);
}

void dialogManager::loadMetaData(LPCWCHAR fileName)
{
	//메타데이터 읽어와서 벡터에 넣어주기
	_currentFileName = fileName;

	WCHAR dir[256];
	ZeroMemory(dir, sizeof(dir));
	swprintf_s(dir, L"%s.txt", _currentFileName);

	_storyMetaData = TXTDATA->wtxtLoad(dir);
	_metaDataNum = -1;
	_scriptNum = 0;

	//한 번 읽어오기
	loadScript();

	_print = true;
}

void dialogManager::loadScript()
{
	//대사 끝나면 쫑
	if (_metaDataNum + 2 >= _storyMetaData.size()) {
		_print = false;
		return;
	}

	for (_metaDataNum = _metaDataNum + 2; _metaDataNum < _storyMetaData.size(); _metaDataNum++) {
		if ((_storyMetaData[_metaDataNum][0] == L'\r') ||
			(_storyMetaData[_metaDataNum][0] == L'\n')) continue;

		else break;
	}

	_scriptNum++;
}

void dialogManager::resetTimer()
{
	TIMEMANAGER->endTimer();
	TIMEMANAGER->setTimer();
	UIMANAGER->getCurrentDownMenu()->setHidden(false);
}

void dialogManager::addItemLog(Player * player, Item * item)
{
	resetTimer();

	WCHAR log[128];
	swprintf_s(log, L"%s(이)가 %s(을)를 주웠다.", player->getPokemon()->getName().c_str(), item->getName().c_str());
	_battleLog.push_back(log);
}

void dialogManager::addExpLog(Player * player, int exp)
{
	resetTimer();

	WCHAR log[128];
	swprintf_s(log, L"%s(이)가 %d경험치를 획득했다.", player->getPokemon()->getName().c_str(), exp);
	_battleLog.push_back(log);
}

void dialogManager::levelUPLog(Player * player, int level)
{
	resetTimer();

	WCHAR log[128];
	swprintf_s(log, L"%s(이)가 %d레벨이 되었다.", player->getPokemon()->getName().c_str(), level);
	_battleLog.push_back(log);
}

void dialogManager::useSkillLog(Player * player, Skill * skill)
{
	resetTimer();

	//31문자까지 1줄
	WCHAR log[128];
	swprintf_s(log, L"%s(이)가 %s(을)를 사용했다.", player->getPokemon()->getName().c_str(), skill->getName().c_str());
	_battleLog.push_back(log);
}

void dialogManager::failSkillLog()
{
	resetTimer();

	WCHAR log[128];
	swprintf_s(log, L"공격은 실패했다.");
	_battleLog.push_back(log);
}

void dialogManager::greatSkillLog()
{
	resetTimer();

	WCHAR log[128] = L"효과가 굉장했다!!!";
	_battleLog.push_back(log);
}

void dialogManager::worseSkillLog()
{
	resetTimer();

	WCHAR log[128] = L"효과가 별로인 듯 하다...";
	_battleLog.push_back(log);
}

void dialogManager::noneSkillLog()
{
	resetTimer();

	WCHAR log[128] = L"효과가 없는 듯 하다...";
	_battleLog.push_back(log);
}

void dialogManager::hitDamageLog(Player * player, int damage)
{
	resetTimer();

	WCHAR log[128];
	swprintf_s(log, L"%s(이)가 %d의 피해를 입었다.", player->getPokemon()->getName().c_str(), damage);
	_battleLog.push_back(log);
}
