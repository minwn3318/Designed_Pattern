#include "header.h"
using namespace std;

Bullet::Bullet()
{
	this->speed = 0;
}

Bullet_dev::Bullet_dev()
{
	this->speed = 15;
}

Bullet* Bullet_dev::Clone()
{
	return new Bullet_dev(*this);
}



BulletSpawner::BulletSpawner()
{
	bulletList[0] = new Bullet_dev;
}

Bullet* BulletSpawner::CreateBullet(int num)
{
	return bulletList[num]->Clone();
}