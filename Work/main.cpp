#include "header.h"


int main()
{
	Monster_Spawner* mobSpawner = new Monster_Spawner;
	Monster* m1 = mobSpawner->Spawn(0);
	Monster* m2 = mobSpawner->Spawn(0);

	cout << "변경전 1과 2의 스피드 :" << endl;
	cout << m1->GetSpeed() << endl;
	cout << m2->GetSpeed() << endl;

	mobSpawner->ChangeSpeed(0, 20);
	Monster* m3 = mobSpawner->Spawn(0);
	Monster* m4 = mobSpawner->Spawn(0);

	cout << "스포너 속도 변경후 3과 4의 스피드 :" << endl;
	cout << m3->GetSpeed() << endl;
	cout << m4->GetSpeed() << endl;
	cout << "스포너 속도 변경 1과 2의 스피드 :" << endl;
	cout << m1->GetSpeed() << endl;
	cout << m2->GetSpeed() << endl;

	m1->SetSpeed(30);
	cout << "1의 스피드 변경 후 1과 2의 스피드 :" << endl;
	cout << m1->GetSpeed() << endl;
	cout << m2->GetSpeed() << endl;

	return 0;
}
