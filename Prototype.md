# 프로토타입
------
## 프로토타입입 사용 이유
> 예를 들어 몬스터가 등장하는 스포너가 있다.
>  몬스터 종류마다 스포너가 따로 존재하는데 이러면 한 가지 스포너는 한 가지 몬스터 인스턴스만 만든다.
> 게임에 나오는 모든 몬스터를 지원하기 위해 일단 마구잡이로 몬스터 클래스마다
 클래스를 만든다고 하면 스포너 클래스 상속 구조가 몬스터 클래스 상속 구조를 따라가므로 

```
class Spawner{
public:
    virtual ~Spawner() {}
    virtual Monster* spawnMonster() =0;
};
class GhostSpawner :public Spawner{
public:
    virtual Monster* spawnMonster(){
        return new Ghost();
    }
};
... class DemonSpawner : public Spawner{
public:...
```
이 코드는 클래스도 많고 프로그램의 실행과 직접적으로는 관계가 없는 코드, 반복 코드,, 중복 코드 도 많다. 

이를 해결하기 위해 프로토타입을 사용하는데 
원형이 되는 상위 클래스인 Monster에 추상 메서드 clone()을 추가 한다.

```
class Monster{
public:
    virtual ~Monster() {}
    virtual Monster* clone() =0;
...
};
```
하위 클래스에서는 자신과 자료형과 상태가 같은 새로운 객체를 반환하도록 clone()을 구형한다.

```
class Ghost : public Monster{
public:
    Ghost(int health, int speed)
    : health_(health), speed_(speed){}
    virtual Monster* clone() {
        return new Chost(heath_, speed_);
}
private:
    int health_;
    int speed_;
};
```
Monster를 상속받는 모든 클래스에 clone이 메서드가 있다면, 스포너 클래스를 종류별로 만들 필요 없이 하나만 만들면 된다. 

```
class Spawner{
public:
    Spawner(Monster* prototype): prototype_(prototype){}
    Monster* spawnMonster() {
        return prototype_->clone();
    }
private:
    Monster* prototype_;
};
```
Spawner 클래스 내부에는 Monster(프로토 타입) 객체가 숨어 있다. 이 객체는 자기와 같은 Monster 객체를 도장 찍듯 만들어내는 스포너 역할만 한다.


- 요약
    - 프로토타입 패턴은 원형이 되는 오브젝트를 가지고 있다가 이를 Clone 하여 (deep copy) 여러 오브젝트를 만들어 내는 패턴이다.
    -  이때 원형이 되는 오브젝트를 프로토타입이라고 한다.

-------------------------------
## 예제 소스로 '프로토타' 분석

```C++
#include <iostream>
#include <list>
#include <iterator>
#include <map>
using namespace std;

class Position {
  public : 
    Position() {}
    Position(int x, int y) { x_ = x; y_ = y; }
    int x_, y_;
};

class Graphic {
  public :
    virtual void Draw(Position& pos) = 0;
    virtual Graphic* Clone() = 0;
};

class Triangle : public Graphic {
  public :
    void Draw(Position& pos) {}
    Graphic* Clone() { return new Triangle(*this); }
};

class Rectangle : public Graphic {
  public : 
    void Draw(Position& pos) {}
    Graphic* Clone() { return new Rectangle(*this); }
};

class GraphicComposite : public Graphic {
  public : 
    void Draw(Position& pos) {}
    Graphic* Clone() { 
      GraphicComposite *pGraphicComposite = new GraphicComposite(*this);
      list<Graphic*>::iterator iter1;
      list<Graphic*>::iterator iter2;

      iter2 = pGraphicComposite->components_.begin();
      for (iter1 = components_.begin(); iter1 != components_.end(); iter1++) {
        Graphic* pNewGraphic = (*iter1)->Clone();
        *iter2 = pNewGraphic;
        iter2++;
      }

      return pGraphicComposite;
    }

  private : 
    list<Graphic*> components_;
};

class Document {
  public :
    void Add(Graphic* pGraphic) {}
};

class Mouse {
  public :
    bool IsLeftButtonPushed() { 
      static bool isPushed = false;
      // -- GUI 함수 활용 Left Button 상태 체크
      isPushed = ! isPushed;
	  return isPushed;
    }

    Position GetPosition() {
      Position pos;
      // -- GUI 함수 활용 현재 마우스 위치 파악
      return pos;
    }
};

Mouse _mouse; // -- Global Variable

class GraphicEditor {
  public : 
    void AddNewGraphics(Graphic* pSelected) {
      Graphic* pObj = pSelected->Clone();
      while (_mouse.IsLeftButtonPushed()) {
        Position pos = _mouse.GetPosition();
        pObj->Draw(pos);
      }

      curDoc_.Add(pObj);
    }

  private :
    Document curDoc_;
};

class Palette {
  public :
    Palette() {
      Graphic* pGraphic = new Triangle;
      items_[1] = pGraphic;

      pGraphic = new Rectangle;
      items_[2] = pGraphic;

      // -- 필요한 만큼 등록 
    }

    void RegisterNewGraphic(Graphic* pGraphic) {
      items_[items_.size()+1] = pGraphic;
    }

    Graphic* GetSelectedObj() {
      return items_[GetItemOrder()];
    }

    int GetItemOrder() {
      int i=1;
      Position curPos = _mouse.GetPosition();
      // -- 현재 마우스 위치가 몇 번째 항목을 지정하는 지 판별
      return i;
    }

  private :
    map<int, Graphic*> items_;
};

void
main()
{
  Palette palette;
  GraphicEditor ged;

  ged.AddNewGraphics(palette.GetSelectedObj());
}
```

- 프로토 타입 패턴
  -Graphic (프로토타입)클래스:
   Graphic 클래스는 Draw(Position& pos)와 Clone()이라는 가상 함수를 정의하고 있다. Clone() 함수는 이 클래스를 상속하는 클래스에서 구현해야 한다.

  -Triangle 및 Rectangle 클래스:
   Triangle 및 Rectangle 클래스는 Graphic 클래스를 상속하고 있다. 이 두 클래스에서는 Clone() 메서드가 구현되어 기존 객체를 복제하는 기능을 제공한다. 새로운 Triangle 또는 Rectangle 객체가 필요할 때, 해당 클래스의 인스턴스를 복제하여 사용할 수 있다.

  -GraphicComposite 클래스:
   GraphicComposite 클래스는 여러 개의 Graphic 객체를 담는 리스트인 components_를 가지고 있다.
   Clone() 메서드는 이 리스트에 있는 각 Graphic 객체를 복제하고, 이를 새로운 GraphicComposite 객체에 추가하여 복합 그래픽 객체를 복제한다.

- main() 함수에서
  - palette.GetSelectedObj() 함수는 프로토타입 패턴을 활용하고 있다.
  - 이 함수는 선택된 그래픽 객체의 복제본을 반환한다. 프로토타입 패턴을 사용함으로써 Triangle 또는 Rectangle 객체의 복사를 쉽게 수행할 수 있다.
  - 즉, 선택된 그래픽 객체를 프로토타입으로 사용하여 필요할 때마다 복제하여 새로운 객체를 생성할 수 있다.




