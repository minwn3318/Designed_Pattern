#include <iostream>
#include <string>
using namespace std;

class Mob {
public :
	virtual ~Mob() {}
	virtual Mob* clone() = 0;
	virtual string getMeat() = 0;
	virtual string getItem() = 0;
};

class Cow : public Mob {
private :
	string meat = "beef";
	string milk = "milk";

public :
	~Cow() {}
	Mob* clone()
	{
		return new Cow();
	}
	string getMeat()
	{
		return meat;
	}
	string getItem()
	{
		return milk;
	}
};

class Sheep : public Mob {
private:
	string wool = "wool";
	string meat = "lamp";

public:
	~Sheep() {}
	Mob* clone()
	{
		return new Sheep();
	}
	string getMeat()
	{
		return meat;
	}
	string getItem()
	{
		return wool;
	}
};

class Chickin : public Mob {
private:
	string egg = "egg";
	string meat = "chickin";

public:
	~Chickin() {}
	Mob* clone()
	{
		return new Chickin();
	}
	string getMeat()
	{
		return meat;
	}
	string getItem()
	{
		return egg;
	}
};

class Spawner {
	static Mob* prototyeMobs[3];
	static int mob_type;
public :
	static void init()
	{
		prototyeMobs[0] = new Cow();
		prototyeMobs[1] = new Sheep();
		prototyeMobs[2] = new Chickin();
	}

	static void remove()
	{
		delete prototyeMobs[0];
		delete prototyeMobs[1];
		delete prototyeMobs[2];
	}

	static Mob* make(const int index)
	{
		if (index >= mob_type)
		{
			return nullptr;
		}
		return prototyeMobs[index]->clone();
	}

};

Mob* Spawner::prototyeMobs[3];
int Spawner::mob_type = 3;

int main()
{
	Spawner::init();
	
	Mob* cow1 = Spawner::make(0);
	Mob* sheep1 = Spawner::make(1);
	Mob* chickin1 = Spawner::make(2);

	cout << "get meat for cow : " << cow1->getMeat() << endl;
	cout << "get meat for sheep : " << sheep1->getMeat() << endl;
	cout << "get meat for chickin : " << chickin1->getMeat() << endl;
	cout << endl;
	cout << "get milke : " << cow1->getItem() << endl;
	cout << "get wool : " << sheep1->getItem() << endl;
	cout << "get egg : " << chickin1->getItem() << endl;

	Mob* cow2 = Spawner::make(0);

	cout << endl;
	cout << "address cow1 : " << cow1 << endl;
	cout << "address &cow1 : " << &cow1 << endl;
	cout << endl;
	cout << "address cow2 : " << cow2 << endl;
	cout << "address &cow2 : " << &cow2 << endl;
	cout << endl;
	cout << "address sheep1 : " << sheep1 << endl;
	cout << "address &sheep1 : " << &sheep1 << endl;
	cout << endl;
	cout << "address chickin1 : " << chickin1 << endl;
	cout << "address &chickin1 : " << &chickin1 << endl;

	Spawner::remove();

	return 0;
}