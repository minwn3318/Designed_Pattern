반복자 패턴 (Iterator Pattern)   
=============      
## 반복자 패턴 사용 이유   
데이터 집합을 색인할 때, 데이터집합의 표현을 드러내지 않기 위해, 데이터 집합에서 순회 알고리즘만 분리하여 유연성 있게 순회할 수 있도록 하기위해 구현되었다.   

- 요약
  - 반복자 패턴이란 디자인 패턴 중 행동 패턴으로 여러 데이터 집합 즉, 자료구조를 선회하며 요소를 추출할 때, 자료구조의 구현을 드러내지 않고, 요소에 접근할 수 있도록하는 디자인 패턴이다.   

-------------
## 반복자 패턴 분석   
```
/*
 * C++ Design Patterns: Iterator
 * Author: Jakub Vojvoda [github.com/JakubVojvoda]
 * 2016
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>
#include <stdexcept>
#include <vector>

class Iterator;
class ConcreteAggregate;

/*
 * Aggregate
 * defines an interface for aggregates and it decouples your
 * client from the implementation of your collection of objects
 */
class Aggregate
{
public:
  virtual ~Aggregate() {}
  
  virtual Iterator *createIterator() = 0;
  // ...
};

/*
 * Concrete Aggregate
 * has a collection of objects and implements the method
 * that returns an Iterator for its collection
 *
 */
class ConcreteAggregate : public Aggregate
{
public:
  ConcreteAggregate( const unsigned int size )
  {
    list = new int[5] {1,2,3,4,5};
    count = size;
  }
  
  ~ConcreteAggregate()
  {
    delete[] list;
  }
  
  Iterator *createIterator();
  
  unsigned int size() const
  {
    return count;
  }
  
  int at( unsigned int index )
  {
    return list[ index ];
  }
  // ...

private:
  int *list;
  unsigned int count;
  // ...
};

/*
 * Iterator
 * provides the interface that all iterators must implement and
 * a set of methods for traversing over elements
 */
class Iterator
{
public:
  virtual ~Iterator() { /* ... */ }
  
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual int currentItem() const = 0;
  // ...
};

```
- 색인 객체와 컬렉션 객체가 존재해야 한다.   
- 색인 객체와 컬렉션 객체는 인터페이스와 구현 클래스로 나뉜다.   
- 색인 객체는 컬렉션 객체에 포함되며 종합적인 구조를 띈다.   
- 구현 클래스는 인터페이스를 상속한다.   
- 인터페이스는 순수가상함수로 되어있다.   
