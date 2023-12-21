#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;





//��� ���� �����ϴ� Ŭ���� ----------
class ScoreManager
{
private:
	int score = 0; //����
	static ScoreManager* instance; //��ü ���� ����
	ScoreManager() {} //�ܺο��� ȣ���� �� ������ ������ ��������
public:
	static ScoreManager* GetInstance(); //�������� ��ü �ʱ�ȭ
	void addScore(int newpoints);		//���� �ø���
	int getScore() { return score; } 	//���� ���� �˷��ִ� �Լ�
};

// ���� ������ Ŭ���� ���� <- ghost, ghostBoss -----------
class Monster {
protected:
	int speed; //�ӵ�
	int score; //����
	int health; //ü��
	string name; //�̸�
public:
	Monster(); // ������
	virtual Monster* Clone() = 0; //����
	virtual void SetSpeed(int spe); //�ӵ����� - �����Լ�
	virtual int GetSpeed() { return speed; } //������ȯ �Լ� - �����Լ�
	virtual string GetName() { return name; } // �̸���ȯ �Լ� - �����Լ�
	virtual ~Monster() { cout << "delet Monster" << endl; } //���� �Ҹ���
};

class Ghost : public Monster { //������Ÿ���� �ڽ� Ŭ����
public:
	Ghost(); // ������
	Monster* Clone(); // ����
	~Ghost() { cout<< "delete Ghost" << endl; } //�Ҹ���
};

class GhostBoss : public Monster {
public:
	GhostBoss(); //������
	Monster* Clone(); //����
	~GhostBoss() { cout << "delete Boss" << endl; } //�Ҹ���
};

//���� ���� ���丮 Ŭ����
class Monster_Spawner { 
private:
	Monster* spawnList[2]; //������Ÿ���� ������ �迭
public:
	Monster_Spawner(); //�ʱ�ȭ
	void ChangeSpeed(int num, int spe); //�迭�� ��ü, �ӵ� ����
	Monster* Spawn(int num); //�迭���� ��ü �����Ͽ� ����
	~Monster_Spawner() {cout << "delet spawner" << endl; }
};





// �Ѿ� ������Ÿ�� Ŭ���� <- Bullet_dev ����--------------
class Bullet {
protected:
	int speed; // �ӵ�
public :
	Bullet(); // �ʱ�ȭ
	virtual Bullet* Clone() = 0; //���� - �����Լ�
	virtual ~Bullet() { cout << "delet Bullet" << endl; } // ����Ҹ���
};

class Bullet_dev : public Bullet { //������Ÿ���� ��ӹ޴� �ڽ� Ŭ����
public :
	Bullet_dev(); // �ʱ�ȭ
	Bullet* Clone(); // ����
	~Bullet_dev() { cout << "Bullet_dev" << endl; } // �Ҹ���
};

// �Ѿ� ���� ���丮 Ŭ����
class BulletSpawner
{
private :
	Bullet* bulletList[1]; //������Ÿ���� ������ �迭
public :
	BulletSpawner(); //�迭 �ʱ�ȭ
	Bullet* CreateBullet(int num); //�迭���� ��ü �����Ͽ� ����
	~BulletSpawner() { cout << "delete bulletspawner" << endl; }
};





// �����̳��� �ݺ��� Ŭ���� -----------------------
template<typename T, typename U>
class Iter_VecQueue {
public:
	//vector�ݺ��� �̸��� iter_type���� ������
	//typename ��� ������ typename T�� ���� ����
	//typedef�� �������Ѵٴ� Ű����
	typedef typename std::vector<T>::iterator iter_type;

	Iter_VecQueue(U* containerType); //�����̳��� ���� �ݺ��ڸ� �޴� ������
	void First(); //ù��° �����ġ ����Ű��
	void Next(); //������� ��ġ�� �Ѿ��  
	bool IsDone();
	iter_type Current()//���� ��� ��ġ ��ȯ
	{
		return itr;
	}
private:
	U* containerPtr; //�����̳� ���� ����
	iter_type itr; //�����ǵ� �ݺ���
};

template<typename T, typename U>
Iter_VecQueue<T, U>::Iter_VecQueue(U* containerType) : containerPtr(containerType)
{
	/*
	1. �����̳� Ŭ������ ������ �Ű������� �޴´�
	2. �ݺ��� Ŭ������ �����̳� ���������� �Ű�����()�� �ʱ�ȭ �Ѵ�
	3. �ݺ��� Ŭ������ �����ǵ� �ݺ��ڸ� 
	�ݺ��� �Ű������� �ʱ�ȭ�� �����̳� ���� ����(2.�� �ʱ�ȭ�� ��)���� 
	�Ű������� ó�� ���� �ݺ��ڷ� �ʱ�ȭ�Ѵ�.
	*/

	this->itr = containerPtr->containerReal.begin();
}

template<typename T, typename U>
void Iter_VecQueue<T, U>::First() //������ ȣ��� ����
{
	this->itr = containerPtr->containerReal.begin();
}

template<typename T, typename U>
void Iter_VecQueue<T, U>::Next()
//�����ǵ� �ݺ��ڴ� ������ ���� �ݺ��ڸ� �ٸ� �̸����� �ٲ۰��̹Ƿ� ++������ �����ϴ� 
{
	this->itr++;
}

template<typename T, typename U>
bool Iter_VecQueue<T, U>::IsDone()
{
	return (itr == containerPtr->containerReal.end());
}

// �����̳� Ŭ���� <- ���ͱ������ Ž���� ������ ť�� ����
template<typename T>
class VecQueue {
	//������ ���� -> �ش� Ŭ�������� VecQueue�� ���뿡 �������� ������ ���������� ������� �ش�
	friend class Iter_VecQueue<T, VecQueue>;
public :
	Iter_VecQueue<T, VecQueue>* CreateIter_VecQueue()//�ݺ��� ��ü�� �����Ѵ�
	{
		// ���� �����̳� Ŭ���� ��ü�� �����͸� �̿��� �ݺ��� Ŭ������ �����ڸ� ȣ���Ѵ�.
		return new Iter_VecQueue<T, VecQueue>(this);
	}
	void PushQueue(T a); //�տ��� ��Ҹ� �־��ش�
	void PopQueue(); //�տ��� ��Ҹ� ���ش�
	size_t RealSize(); //��� ������ Ȯ���Ѵ�
	~VecQueue() { cout << "delete VecQueue" << endl; }
private:
	vector<T> containerReal; //�����̳� ����
};

template<typename T>
void VecQueue<T>::PushQueue(T a)
{
	this->containerReal.push_back(a);
}

template<typename T>
void VecQueue<T>::PopQueue()
{
	//�˰��� ���ø��� �̿��� �ڹٱͼ� �������Ͽ� �ڿ��� ���� �ٽ� ���󺹱� ��Ų�� 
	reverse(containerReal.begin(), containerReal.end());
	containerReal.pop_back();
	reverse(containerReal.begin(), containerReal.end());
}

template<typename T>
size_t VecQueue<T>::RealSize()
{
	return this->containerReal.size();
}


//����Ž�� �˰���
template<typename S, typename U>
bool search_binary(S& list,const U& type)
{
	
}


 //�� �ۻ���� Ŭ���� <- �����̳�
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