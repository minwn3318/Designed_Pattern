#include "header.h"


ScoreManager* ScoreManager::GetInstance()
{
	//만약 객체에 아무것도 없을 때 새로 객체를 생성하여 
	//할당하고, 객체값으로 반환한다
	if (instance == nullptr) {
		instance = new ScoreManager;
	}
	return instance;
}

//더하기
void ScoreManager::addScore(int newpoints)
{
	score += newpoints;
}

//전역에서 초기화 한다. 딱 한번만 하면된다.
ScoreManager* ScoreManager::instance = nullptr;