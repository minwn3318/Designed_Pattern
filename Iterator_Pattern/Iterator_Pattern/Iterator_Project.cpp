#include <iostream>
#include <vector>
using namespace std;

class ItemItr {
public :
	virtual void first() = 0;
};

class Self {
public :
	virtual ItemItr* createItr() = 0;
};

class Item {
protected :
	string name;
public :
	virtual Item* clone() = 0;
	virtual void setName(string n) = 0;
	virtual string getName() = 0;
	virtual void useItem() = 0;
};

class Book : public Item {
public :
	Item* clone()
	{
		return new Book();
	}
	void setName(string n)
	{
		this->name = n;
	}
	string getName()
	{
		cout << "name : " <<this->name << endl;
	}
	void useItem()
	{
		cout << "using" << endl;
	}
};

class Pot : public Item {
public:
	Item* clone()
	{
		return new Pot();
	}
	void setName(string n)
	{
		this->name = n;
	}
	string getName()
	{
		cout << "name : " << this->name << endl;
	}
	void useItem()
	{
		cout << "using" << endl;
	}
};

class PhotoFrame : public Item {
public:
	Item* clone()
	{
		return new PhotoFrame();
	}
	void setName(string n)
	{
		this->name = n;
	}
	string getName()
	{
		cout << "name : " << this->name << endl;
	}
	void useItem()
	{
		cout << "using" << endl;
	}
};

class ItemItr_con : public Item {

};

class Self_con : public Self {

};

class Person {
private :
	Person() {}
	static Person* instance;
public :
	static Person getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Person();
		}

		return *instance;
	}
};

int main()
{
	return 0;
}