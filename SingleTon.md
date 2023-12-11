# 싱글턴
------
## 싱글턴 사용 이유
> 인스턴스가 여러 개면 제대로 작동하지 않는 상황이 종종 있다. 
즉 여러 작업이 동시에 진행될 수 있으므로 작업들을 서로 조율해야 한다. 
한쪽에서는 파일을 생성하고 다른 한쪽에서는 방금 생성한 파일을 삭제하려고 한다면,
래퍼 클래스가 두 작업을 다 파악해서 서로 간섭하지 못하게 해야 한다.
  이를 위해서 클래스로 들어온 호출이 이전 작업 전체에 대해 접근 할 수 있어야 한다.
 아무데서나 클래스 인스턴스를 만들 수 있다면 다른 인스턴스에서 어떤 작업을 진행 중인지를 알 수 없다.
  이를 싱글턴으로 만들면 클래스가 인스턴스를 하나만 가지도록 컴파일 단계에서 강제 할 수 있다.

- 요약
    - 전역 변수를 사용하지 않고 인스턴스를 하나만 생성하도록 하며 생성된 인스턴스를 어디서든 사용할 수 있는 패턴이다. 
    인스턴스를 여러 개 만들면 자원을 낭비하거나 버그를 발생시킬 수 있으므로 오직 하나만 생성한다.

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



