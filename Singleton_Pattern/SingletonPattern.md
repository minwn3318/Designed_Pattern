# 싱글턴
------
## 싱글턴 사용 이유
    전역 변수를 사용하지 않고 인스턴스를 하나만 생성하도록 하며 생성된 인스턴스를 어디서든 사용할 수 있는 패턴이다. 
    인스턴스를 여러 개 만들면 자원을 낭비하거나 버그를 발생시킬 수 있으므로 오직 하나만 생성한다.
----

## 싱글턴 구성
1. 게으른 초기화: 
- 어떠한 전역 객체의 생성자에서 위 싱글톤을 참조하려고 할 때, 싱글톤 객체가 생성되기 이전에 발생할 수 있기 때문에 객체의 생성 시점을 변경을 해야 한다->최초 GetInstance()를 호출을 하게 되는 시점에 생성
2. 클래스 이름을 반환 타입으로 사용:
- 클래스 객체를 저장할 정적 맴버 변수 만들고-> 정적 맴버 함수로 싱글턴 객체에 접근할 수 있도록
3. 외부에서 객체를 만드는것이 아닌 싱글턴 클래스 내부에서 객체 생성:
- 생성자를 private
4.static과 new
- 싱글톤 패턴을 사용하면 최초 한번 new로 객체를 생성하고 해당 객체를 이후에도 사용하도록 공유->메모리 낭비 문제를 방지


------------------------------
## 예제 소스로 '싱글턴' 분석

```C++
#include <iostream>
using namespace std;

#define N_UNIT    100

class GameUnit {
  public :
    static void InitUnitArray() {
       for (int i=0; i < N_UNIT; i++)
         pUnitArray_[i] = 0;
    }

    static GameUnit* CreateInstance() { return 0; }

    static void DestroyUnit(GameUnit* pUnit) {
      for (int i=0; i < N_UNIT; i++) {
        if (pUnitArray_[i] == pUnit) {
          delete pUnitArray_[i];
          pUnitArray_[i] = 0;
          return;
        }
      }
    }

    virtual void Display(int x, int y) = 0;
    virtual void DoAction() = 0;
  protected :
    GameUnit() {}
    GameUnit(const GameUnit& rhs) {}
    static GameUnit* pUnitArray_[N_UNIT];
};

// -- 클래스 변수 정의
GameUnit* GameUnit::pUnitArray_[N_UNIT];

class AttackUnit : public GameUnit {
  public : 
    static GameUnit* CreateInstance() { 
      for (int i=0; i < N_UNIT; i++) {
        if (pUnitArray_[i] == 0) {
          pUnitArray_[i] = new AttackUnit;
          return pUnitArray_[i];
        }
      }

      return 0;
    }

    void Display(int x, int y) {}
    void DoAction() {}
  protected :
    AttackUnit() {}
    AttackUnit(const AttackUnit& rhs) {}
};

class ProtectUnit : public GameUnit {
  public : 
    static GameUnit* CreateInstance() { 
      for (int i=0; i < N_UNIT; i++) {
        if (pUnitArray_[i] == 0) {
          pUnitArray_[i] = new ProtectUnit;
          return pUnitArray_[i];
        }
      }

      return 0;
    }

    void Display(int x, int y) {}
    void DoAction() {}
  protected :
    ProtectUnit() {}
    ProtectUnit(const ProtectUnit& rhs) {}
};

void 
main()
{
  GameUnit::InitUnitArray();

  GameUnit *pUnit1 = AttackUnit::CreateInstance();
  if (pUnit1 == 0)
    cout << "No More Create Unit" << endl;

  GameUnit *pUnit2 = ProtectUnit::CreateInstance();
  if (pUnit2 == 0)
    cout << "No More Create Unit" << endl;

  GameUnit::DestroyUnit(pUnit1);
  GameUnit::DestroyUnit(pUnit2);
}
```

- 전체 흐름
   - GameUnit 클래스가 싱글턴 패턴을 구현하고 있다.
   - GameUnit 클래스는 게임 유닛을 나타내는 추상 클래스로, AttackUnit과 ProtectUnit이라는 두 가지 구체적인 유닛 클래스가 이를 상속하고 있다. 
   - GameUnit 클래스에는 게임 유닛을 생성하고 관리하기 위한 배열인 pUnitArray_가 정의되어 있다. (이 배열은 최대 N_UNIT(100)개의 게임 유닛을 저장할 수 있다.)

- 싱글턴 패턴
  - ‘InitUnitArray()’은 ‘pUnitArray_’ 배열을 초기화하는 함수이다.
  - ‘CreateInstance()’은 싱글턴 패턴을 적용하여 유닛 인스턴스를 생성하는 함수이다. 배열에서 빈 공간을 찾아 해당 인스턴스를 저장하고 반환한다.
  - ‘DestroyUnit(GameUnit* pUnit)’은 주어진 유닛 인스턴스를 배열에서 찾아 삭제하고 메모리를 해제하는 함수이다.

- main() 함수에서
  - GameUnit::InitUnitArray()를 호출하여 배열을 초기화
  - AttackUnit::CreateInstance() 및 ProtectUnit::CreateInstance()를 통해 유닛 인스턴스를 생성하고 제거하는 예시가 포함되어 있다.
