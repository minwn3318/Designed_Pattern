퍼사드 패턴  (Facade Pattern)   
=============      
## 퍼사드 패턴 사용 이유   
대개 하나의 행동을 구현할 때 여러 객체를 사용하여야 하는 경우가 있다. 그러면 하나의 행동을 실행하기 위해 여러 객체를 생성하는 불편함과 코드의 가독성이 떨어지는 문제가 발생한다. 따라서 하나의 객체를 사용하면서 하위 객체들을 사용할 수 있게 하고, 가독성을 높여주기 위해 퍼사드 패턴이 고안되었다.   

- 요약
  - 퍼사드 패턴은 디자인 패턴중 구조 패턴으로 여러 개의 하위 클래스들을 공통적인 상위클래스로 묶어 간편하게 하위 클래스의 객체를 사용할 수 있도록 한 디자인 패턴이다.    
------------------------------
## 예제 소스로 '퍼사드' 분석   
- 분석용 출처 :
- 참조용 :
  https://github.com/JakubVojvoda/design-patterns-cpp/blob/master/facade/Facade.cpp
  
```
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <iterator>
using namespace std;

class SearchCond {
  public :
    SearchCond(map<string, string> nvList) {
      condList_ = nvList;
    }

    bool CheckCond() {
      // -- name, value 쌍들의 리스트에 대해 검색 조건을 검사한다.
      // 예를 들어, age에 대해 숫자가 아닌 값이 설정되면 안되며, 
      // 음수값등이 설정되면 안 된다. 
      return true;
    }
  private :
    map<string, string> condList_;
};

class ListData {
  // -- 데이터베이스에서 검색되는 결과 레코드가 저장되기 위한 자료구조
};

class ListDBResult {
  public :
    int GetCount() {
      return result_.size();
    }

    void InitIterator() {
      iter_ = result_.begin();
    }

    ListData GetNextData() {
      return *iter_++;
    }
  private:
    list<ListData> result_;
    list<ListData>::iterator iter_;
};

class Database {
  public :
    Database() {
      // -- 데이터베이스 관리 시스템과 연결을 수행함.
    }

    bool Execute(string sql, ListDBResult& result) {
      // -- sql 수행 결과를 result에 설정하되, sql 수행 과정에서 
      // 문제가 있으면 false를 return하며, 그렇지 않은 경우에는 
      // true 를 return한다.
      return true;
    }
};

class SQLGenerator {
  public :
    string GenerateSQL(SearchCond cond) {
      string sql;

      // -- 검색 조건에 따라 sql 문장을 생성
      return sql;
    }
};


class DBHandler {
  public :
    bool Search(map<string, string> nvList, ListDBResult& result) {
      SearchCond cond(nvList);
      if (! cond.CheckCond()) {
        cout << "잘못된 검색조건" << endl;
        return false;
      }

      SQLGenerator generator;
      string sql = generator.GenerateSQL(cond);

      return db_.Execute(sql, result);
    }
  private :
    Database db_;
};

void
main()
{
  map<string, string> nvList;
  ListDBResult result;

  DBHandler handler;
  handler.Search(nvList, result);
}
```
- 각 클래스의 역할
  - SearchCond : 데이터 베이스에서 검색기능을 구현한 알고리즘 클래스이다.
  - ListData : 데이터 베이스에 저장될 자료구조 클래스이다.
  - ListDBResult : ListData 자료구조를 타입으로 가지는 데이터베이스를 만들고 반복자 초기화, 요소개수 등 데이터베이스를 관리하는 클래스이다.
  - Database : 데이터베이스 관리 클래스를 연결하고 해당 데이터베이스와 관련된 알고리즘의 수행결과를 반환하는 함수를 가지는 클래스이다
  - SQLGenerator : 수행결과 문장을 생성하는 클래스이다.
  - DBHandler : 위의 클래스들을 사용하고, 연결하는 퍼사드 클래스다.
    
- 퍼사드 패턴 구현 클래스 : 하나의 기능(검색)을 구현하기 위해 하위 클래스들을 사용하고 있다. 클라이언트(메인함수)는 하위 클래스들을 일일이 호출하여 사용할 필요없이 해당 퍼사드 패턴 클래스를 이용하면 된다.
  - 검색함수를 가지고 있다.
    1. 검색함수를 구현했다. 매개변수로 데이터베이스 관리 클래스와 검색알고리즘에 필요한 맵 자료구조를 받는다.
    2. 검색알고리즘 객체를 선언하여 검색알고리즘을 수행한다.
    3. 검색알고리즘에서 반환한 값을 받아 수행결과를 반환하는 클래스를 선언하여 결과 값을 내놓는다.

- 메인함수
  - 검색알고리즘에 필요한 맵 자료구조를 선언한다.
  - 데이터 베이스를 관리하는 클래스를 선언한다.
  - 퍼사드 클래스를 선언한다.
  - 퍼사드 클래스에 있는 검색함수를 사용한다.   
