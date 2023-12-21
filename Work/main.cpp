#include "header.h"


int main()
{
	Monster_Spawner* mobSpawner = new Monster_Spawner;
	Monster* m1 = mobSpawner->Spawn(0);
	Monster* m2 = mobSpawner->Spawn(0);

	cout << "������ 1�� 2�� ���ǵ� :" << endl;
	cout << m1->GetSpeed() << endl;
	cout << m2->GetSpeed() << endl;

	mobSpawner->ChangeSpeed(0, 20);
	Monster* m3 = mobSpawner->Spawn(0);
	Monster* m4 = mobSpawner->Spawn(0);

	cout << "������ �ӵ� ������ 3�� 4�� ���ǵ� :" << endl;
	cout << m3->GetSpeed() << endl;
	cout << m4->GetSpeed() << endl;
	cout << "������ �ӵ� ���� 1�� 2�� ���ǵ� :" << endl;
	cout << m1->GetSpeed() << endl;
	cout << m2->GetSpeed() << endl;

	m1->SetSpeed(30);
	cout << "1�� ���ǵ� ���� �� 1�� 2�� ���ǵ� :" << endl;
	cout << m1->GetSpeed() << endl;
	cout << m2->GetSpeed() << endl;

	return 0;
}
