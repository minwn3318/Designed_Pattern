#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;





//모든 점수 관리하는 클래스 ----------
class ScoreManager
{
private:
	int score = 0; //점수
	static ScoreManager* instance; //객체 전역 변수
	ScoreManager() {} //외부에서 호출할 수 없도록 생성자 접근제한
public:
	static ScoreManager* GetInstance(); //전역에서 객체 초기화
	void addScore(int newpoints);		//점수 올리기
	int getScore() { return score; } 	//현재 점수 알려주는 함수
};

// 몬스터 프로토 클래스 영역 <- ghost, ghostBoss -----------
class Monster {
protected:
	int speed; //속도
	int score; //점수
	int health; //체력
	string name; //이름
public:
	Monster(); // 생성자
	virtual Monster* Clone() = 0; //복사
	virtual void SetSpeed(int spe); //속도설정 - 가상함수
	virtual int GetSpeed() { return speed; } //점수반환 함수 - 가상함수
	virtual string GetName() { return name; } // 이름반환 함수 - 가상함수
	virtual ~Monster() { cout << "delet Monster" << endl; } //가상 소멸자
};

class Ghost : public Monster { //프로토타입의 자식 클래스
public:
	Ghost(); // 생성자
	Monster* Clone(); // 복사
	~Ghost() { cout<< "delete Ghost" << endl; } //소멸자
};

class GhostBoss : public Monster {
public:
	GhostBoss(); //생성자
	Monster* Clone(); //복사
	~GhostBoss() { cout << "delete Boss" << endl; } //소멸자
};

//몬스터 스폰 팩토리 클래스
class Monster_Spawner { 
private:
	Monster* spawnList[2]; //프로토타입을 저장할 배열
public:
	Monster_Spawner(); //초기화
	void ChangeSpeed(int num, int spe); //배열의 객체, 속도 수정
	Monster* Spawn(int num); //배열에서 객체 복사하여 생성
	~Monster_Spawner() {cout << "delet spawner" << endl; }
};





// 총알 프로토타입 클래스 <- Bullet_dev 포함--------------
class Bullet {
protected:
	int speed; // 속도
public :
	Bullet(); // 초기화
	virtual Bullet* Clone() = 0; //복사 - 가상함수
	virtual ~Bullet() { cout << "delet Bullet" << endl; } // 가상소멸자
};

class Bullet_dev : public Bullet { //프로토타입을 상속받는 자식 클래스
public :
	Bullet_dev(); // 초기화
	Bullet* Clone(); // 복사
	~Bullet_dev() { cout << "Bullet_dev" << endl; } // 소멸자
};

// 총알 스폰 팩토리 클래스
class BulletSpawner
{
private :
	Bullet* bulletList[1]; //프로토타입을 저장할 배열
public :
	BulletSpawner(); //배열 초기화
	Bullet* CreateBullet(int num); //배열에서 객체 복사하여 생성
	~BulletSpawner() { cout << "delete bulletspawner" << endl; }
};





// 컨테이너의 반복자 클래스 -----------------------
template<typename T, typename U>
class Iter_VecQueue {
public:
	//vector반복자 이름을 iter_type으로 재정의
	//typename 사용 이유는 typename T가 들어가기 때문
	//typedef가 재정의한다는 키워드
	typedef typename std::vector<T>::iterator iter_type;

	Iter_VecQueue(U* containerType); //컨테이너의 시작 반복자를 받는 생성자
	void First(); //첫번째 요소위치 가리키기
	void Next(); //다음요소 위치로 넘어가기  
	bool IsDone();
	iter_type Current()//현재 요소 위치 반환
	{
		return itr;
	}
private:
	U* containerPtr; //컨테이너 변수 참조
	iter_type itr; //재정의된 반복자
};

template<typename T, typename U>
Iter_VecQueue<T, U>::Iter_VecQueue(U* containerType) : containerPtr(containerType)
{
	/*
	1. 컨테이너 클래스의 참조형 매개변수를 받는다
	2. 반복자 클래스의 컨테이너 변수참조를 매개변수()로 초기화 한다
	3. 반복자 클래스의 재정의된 반복자를 
	반복자 매개변수로 초기화된 컨테이너 변수 참조(2.에 초기화한 애)통해 
	매개변수의 처음 시작 반복자로 초기화한다.
	*/

	this->itr = containerPtr->containerReal.begin();
}

template<typename T, typename U>
void Iter_VecQueue<T, U>::First() //생성자 호출과 같다
{
	this->itr = containerPtr->containerReal.begin();
}

template<typename T, typename U>
void Iter_VecQueue<T, U>::Next()
//재정의된 반복자는 기존의 벡터 반복자를 다른 이름으로 바꾼것이므로 ++연산이 가능하다 
{
	this->itr++;
}

template<typename T, typename U>
bool Iter_VecQueue<T, U>::IsDone()
{
	return (itr == containerPtr->containerReal.end());
}

// 컨테이너 클래스 <- 벡터기반으로 탐색이 가능한 큐로 구성
template<typename T>
class VecQueue {
	//프렌즈 선언 -> 해당 클래스에게 VecQueue의 내용에 엑세스할 권한을 접근지정자 상관없이 준다
	friend class Iter_VecQueue<T, VecQueue>;
public :
	Iter_VecQueue<T, VecQueue>* CreateIter_VecQueue()//반복자 객체를 생성한다
	{
		// 지금 컨테이너 클래스 객체의 포인터를 이용해 반복자 클래스의 생성자를 호출한다.
		return new Iter_VecQueue<T, VecQueue>(this);
	}
	void PushQueue(T a); //앞에서 요소를 넣어준다
	void PopQueue(); //앞에서 요소를 빼준다
	size_t RealSize(); //요소 갯수를 확인한다
	~VecQueue() { cout << "delete VecQueue" << endl; }
private:
	vector<T> containerReal; //컨테이너 변수
};

template<typename T>
void VecQueue<T>::PushQueue(T a)
{
	this->containerReal.push_back(a);
}

template<typename T>
void VecQueue<T>::PopQueue()
{
	//알고리즘 템플릿을 이용해 뒤바귀서 재정렬하여 뒤에서 빼고 다시 원상복귀 시킨다 
	reverse(containerReal.begin(), containerReal.end());
	containerReal.pop_back();
	reverse(containerReal.begin(), containerReal.end());
}

template<typename T>
size_t VecQueue<T>::RealSize()
{
	return this->containerReal.size();
}


//이진탐색 알고리즘
template<typename S, typename U>
bool search_binary(S& list,const U& type)
{
	
}


 //총 퍼사드형 클래스 <- 컨테이너
class Gun {
private :
	BulletSpawner* bulletSpawner;
	VecQueue<Bullet*> magazine;
	bool empty;
public :
	Gun(VecQueue<Bullet*> &m, BulletSpawner* &sp)
	{
		this->bulletSpawner = sp;
		this->magazine = m;
		for (int i = 0; i < 10; i++)
		{
			magazine.PushQueue(bulletSpawner->CreateBullet(0));
		}
		empty = false;
		
	}
	void Filling()
	{
		if (empty)
		{
			for (int i = 0; i < 10; i++)
			{
				magazine.PushQueue(bulletSpawner->CreateBullet(0));
			}
			empty = !empty;
			cout << "Filling Compelet" << endl;
		}
		else
		{
			cout << "It's FULL!!" << endl;
		}
	}
	void Shooting(VecQueue<Monster*>& m, Iter_VecQueue<Monster*, VecQueue<Monster*>>* iter)
	{
		int storScore;
		iter = m.CreateIter_VecQueue();
		
		if (!empty)
		{
			magazine.PopQueue();
			m.PopQueue();
			if (magazine.RealSize() == 0)
			{
				empty = !empty;
			}
		}
		else
		{
			cout << "It's EMPTY!" << endl;
		}
	}
};