#include "header.h"


ScoreManager* ScoreManager::GetInstance()
{
	//���� ��ü�� �ƹ��͵� ���� �� ���� ��ü�� �����Ͽ� 
	//�Ҵ��ϰ�, ��ü������ ��ȯ�Ѵ�
	if (instance == nullptr) {
		instance = new ScoreManager;
	}
	return instance;
}

//���ϱ�
void ScoreManager::addScore(int newpoints)
{
	score += newpoints;
}

//�������� �ʱ�ȭ �Ѵ�. �� �ѹ��� �ϸ�ȴ�.
ScoreManager* ScoreManager::instance = nullptr;