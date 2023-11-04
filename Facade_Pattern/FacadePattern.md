퍼사드 패턴  (Facade Pattern)   
=============   
### 퍼사드 패턴이란?   
퍼사드 패턴은 디자인 패턴중 구조 패턴으로 여러 개의 하위 클래스들을 공통적인 상위클래스로 묶어 간편하게 하위 클래스의 객체를 사용할 수 있도록 한 디자인 패턴이다.    
   
### 퍼사드 패턴이 사용된 이유   
대개 하나의 행동을 구현할 때 여러 객체를 사용하여야 하는 경우가 있다. 그러면 하나의 행동을 실행하기 위해 여러 객체를 생성하는 불편함과 코드의 가독성이 떨어지는 문제가 발생한다. 따라서 하나의 객체를 사용하면서 하위 객체들을 사용할 수 있게 하고, 가독성을 높여주기 위해 퍼사드 패턴이 고안되었다.   
   
### 퍼사드 패턴 분석   
```
/*
 * C++ Design Patterns: Facade
 * Author: Jakub Vojvoda [github.com/JakubVojvoda]
 * 2016
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>

/*
 * Subsystems
 * implement more complex subsystem functionality
 * and have no knowledge of the facade
 */
class SubsystemA
{
public:
  void suboperation()
  {
    std::cout << "Subsystem A method" << std::endl;
    // ...
  }
  void subsuboperation()
  {
      std::cout << "Subsystem A1 method" << std::endl;
  }
  // ...
};

class SubsystemB
{
public:
  void suboperation()
  {
    std::cout << "Subsystem B method" << std::endl;
    // ...
  }
  void subsuboperation()
  {
      std::cout << "Subsystem B1 method" << std::endl;
  }
  // ...
};

class SubsystemC
{
public:
  void suboperation()
  {
    std::cout << "Subsystem C method" << std::endl;
    // ...
  }
  void subsuboperation()
  {
      std::cout << "Subsystem C1 method" << std::endl;
  }
  // ...
};

/*
 * Facade
 * delegates client requests to appropriate subsystem object
 * and unified interface that is easier to use
 */
class Facade
{
public:
  Facade() : subsystemA(), subsystemB(), subsystemC() {}
  
  void operation1()
  {
    subsystemA->suboperation();
    subsystemB->suboperation();
    // ...
  }
  
  void operation2()
  {
    subsystemC->suboperation();
    // ...
  }

  void operation3()
  {
      subsystemC->subsuboperation();
      subsystemA->suboperation();
  }
  // ...
  
private:
  SubsystemA *subsystemA;
  SubsystemB *subsystemB;
  SubsystemC *subsystemC;
  // ...
};


int main()
{
  Facade *facade = new Facade();
  
  facade->operation1();
  facade->operation2();
  facade->operation3();
  delete facade;
  
  return 0;
}

```
- 퍼사드 클래스에는 하위 클래스들의 객체가 포함되어야 한다.   
- 퍼사드 클래스 안의 함수들은 하위 클래스들의 함수를 호출하는 기능이 구현 되어야 한다.   
- 실제 퍼사드 객체를 사용하는 곳에서는 퍼사드 객체에서 퍼사드 함수를 호출해 하위 클래스들의 함수를 호출 할 수 있어야 한다.   
