#include <iostream>
#include <string>
using namespace std;

class Mob {
public :
	virtual ~Mob() {}
	virtual Mob* clone() = 0;
	virtual string getMeat() = 0;
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
	string getMilk()
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
		return new Cow();
	}
	string getMeat()
	{
		return meat;
	}
	string getWool()
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
		return new Cow();
	}
	string getMeat()
	{
		return meat;
	}
	string getMilk()
	{
		return egg;
	}
};

class Spawner {

};

int main()
{
	return 0;
}