#include "header.h"
using namespace std;

Monster::Monster()//초기화
{
	this->speed = 0;
	this->score = 0;
	this->health = 0;
	this->name = '\0';
}
void Monster::SetSpeed(int spe)//속도 설정
{
	this->speed = spe;
}


Ghost::Ghost() // 초기화
{
	this->speed = 10;
	this->score = 10;
	this->health = 50;
	this->name = "Ghsot";
}

Monster* Ghost::Clone()//복사 - new연산자를 이용해 복사생성자로 Monster* 반환
{
	return new Ghost(*this);
}


GhostBoss::GhostBoss()//초기화
{
	this->speed = 10;
	this->score = 25;
	this->score = 100;
	this->name = "Boss";
}

Monster* GhostBoss::Clone()//복사 - new연산자를 이용해 복사생성자로 Monster* 반환
{
	return new GhostBoss(*this);
}



Monster_Spawner::Monster_Spawner()//초기화 - 객체를 새로 생성함
{
	spawnList[0] = new Ghost;
	spawnList[1] = new GhostBoss;
}

Monster* Monster_Spawner::Spawn(int num) 
// 생성(복사) - 초기화시 있던 배열에서 clone을 통한 복사생성자로 객체 복사
{
	return spawnList[num]->Clone();
}

void Monster_Spawner::ChangeSpeed(int num, int spe)// 속도변경 - 원본이 되는 객체의 속도를 수정
{
	spawnList[num]->SetSpeed(spe);
}