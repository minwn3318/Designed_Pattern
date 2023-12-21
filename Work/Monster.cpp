#include "header.h"
using namespace std;

Monster::Monster()//�ʱ�ȭ
{
	this->speed = 0;
	this->score = 0;
	this->health = 0;
	this->name = '\0';
}
void Monster::SetSpeed(int spe)//�ӵ� ����
{
	this->speed = spe;
}


Ghost::Ghost() // �ʱ�ȭ
{
	this->speed = 10;
	this->score = 10;
	this->health = 50;
	this->name = "Ghsot";
}

Monster* Ghost::Clone()//���� - new�����ڸ� �̿��� ��������ڷ� Monster* ��ȯ
{
	return new Ghost(*this);
}


GhostBoss::GhostBoss()//�ʱ�ȭ
{
	this->speed = 10;
	this->score = 25;
	this->score = 100;
	this->name = "Boss";
}

Monster* GhostBoss::Clone()//���� - new�����ڸ� �̿��� ��������ڷ� Monster* ��ȯ
{
	return new GhostBoss(*this);
}



Monster_Spawner::Monster_Spawner()//�ʱ�ȭ - ��ü�� ���� ������
{
	spawnList[0] = new Ghost;
	spawnList[1] = new GhostBoss;
}

Monster* Monster_Spawner::Spawn(int num) 
// ����(����) - �ʱ�ȭ�� �ִ� �迭���� clone�� ���� ��������ڷ� ��ü ����
{
	return spawnList[num]->Clone();
}

void Monster_Spawner::ChangeSpeed(int num, int spe)// �ӵ����� - ������ �Ǵ� ��ü�� �ӵ��� ����
{
	spawnList[num]->SetSpeed(spe);
}