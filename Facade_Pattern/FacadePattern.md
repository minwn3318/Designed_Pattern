퍼사드 패턴  (Facade Pattern)   
=============   
### 퍼사드 패턴이란?   
퍼사드 패턴은 디자인 패턴중 구조 패턴으로 여러 개의 하위 클래스들을 공통적인 상위클래스로 묶어 간편하게 하위 클래스의 객체를 사용할 수 있도록 한 디자인 패턴이다.    
   
### 퍼사드 패턴이 사용된 이유   
대개 하나의 행동을 구현할 때 여러 객체를 사용하여야 하는 경우가 있다. 그러면 하나의 행동을 실행하기 위해 여러 객체를 생성하는 불편함과 코드의 가독성이 떨어지는 문제가 발생한다. 따라서 하나의 객체를 사용하면서 하위 객체들을 사용할 수 있게 하고, 가독성을 높여주기 위해 퍼사드 패턴이 고안되었다.   
   
------------------------------
## 예제 소스로 '퍼사드' 분석
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
- 퍼사드 클래스에는 하위 클래스들의 객체가 포함되어야 한다.   
- 퍼사드 클래스 안의 함수들은 하위 클래스들의 함수를 호출하는 기능이 구현 되어야 한다.   
- 실제 퍼사드 객체를 사용하는 곳에서는 퍼사드 객체에서 퍼사드 함수를 호출해 하위 클래스들의 함수를 호출 할 수 있어야 한다.   
