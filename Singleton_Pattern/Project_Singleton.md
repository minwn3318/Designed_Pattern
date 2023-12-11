# 슈팅게임에서 점수관리하는 싱글톤 구현하기!
(+프로토타입, 스포너(기본 몬스터, 보스몬스터 코드 구현 X))


```C++
#include<iostream>
using namespace std;

class ScoreManager//모든 점수 관리하는 싱글턴
{
private:
	int score=0;

	static ScoreManager* instance;

	ScoreManager() {}
public:
	static ScoreManager* GetInstance()
	{
		if (instance == nullptr) {
			instance = new ScoreManager;
		}
		return instance;
	}

	void addScore(int newpoints) //점수가 오르는 것을 관리하는 함수
	{
		score += newpoints;

	}

	//나중에 일정 점수가 되면 공격력이 쎄지게 하기 위해 현재 점수 알려주는 함수
	int getScore() {
		return score;
	}

};

ScoreManager* ScoreManager::instance = nullptr;  //자료형 이름 클래스 이름::static 변수 이름 = 초기화 할 값

//몬스터
class Monster {
private:
	bool alive = true; //private or public..
	int health=20;
	int speed=5;

public:
	virtual ~Monster(){}
	virtual Monster* clon();

public:
	//기본 몬스터 죽이면 점수 10점 추가
	virtual void basisMobDestory() {
		ScoreManager::GetInstance()->addScore(10); //GetInstance 함수를 통해 인스턴스를 얻고 AddScore 함수에 접근
		
	}
	//보스 몬스터 죽이면 점수 100점 추가
	virtual void bossMobDestory() {
		ScoreManager::GetInstance()->addScore(100);
	}

	//몬스터를 죽이지 못하면 -10점 주기 구현..

};

//스포너 (템플릿 타입 매개변수로 전달하기만 하면 됨.)
//우리 프로젝트에서는 기본 몬스터, 보스몬스터의 클래스를 만들어서 하는게 아니여서 이 스포너는 필요없음..
class Spawner {
public:
	virtual ~Spawner() {}
	virtual Monster* spawnMonster()= 0;
};
```
