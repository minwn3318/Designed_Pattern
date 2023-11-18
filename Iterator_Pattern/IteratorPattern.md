반복자 패턴 (Iterator Pattern)   
=============      
## 반복자 패턴 사용 이유   
데이터 집합을 색인할 때, 데이터집합의 표현을 드러내지 않기 위해, 데이터 집합에서 순회 알고리즘만 분리하여 유연성 있게 순회할 수 있도록 하기위해 구현되었다.   

- 요약
  - 반복자 패턴이란 디자인 패턴 중 행동 패턴으로 여러 데이터 집합 즉, 자료구조를 선회하며 요소를 추출할 때, 자료구조의 구현을 드러내지 않고, 요소에 접근할 수 있도록하는 디자인 패턴이다.   

-------------
## 반복자 패턴 분석   
```
#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
using namespace std;

static const int NA_POS = -1;

class RegularExp {
  public :
    virtual bool Match(string context) = 0;
};

class LiteralExp : public RegularExp {
  public :
    LiteralExp(const char *pStr) : literal_(pStr) { }
    LiteralExp(const string str) : literal_(str) { }

    bool Match(string context) {
      string str;
      ifstream ifs(context.data());
      while (! ifs.eof()) {
        ifs >> str;
        if (literal_ == str) 
          return true;
      }
      return false;
    }
  private :
    string literal_;
};

class OrExp : public RegularExp {
  public :
    OrExp(RegularExp *pExp1, RegularExp *pExp2)
      : pOrExp1_(pExp1), pOrExp2_(pExp2) { }

    bool Match(string context) {
      if (pOrExp1_->Match(context))
        return true;
      else {
        return pOrExp2_->Match(context);
      }
    }
  private :
    RegularExp *pOrExp1_;
    RegularExp *pOrExp2_;
};

class AndExp : public RegularExp {
  public : 
    AndExp(RegularExp *pExp1, RegularExp *pExp2)
      : pAndExp1_(pExp1), pAndExp2_(pExp2) { }

    bool Match(string context) {
      return pAndExp1_->Match(context) && pAndExp2_->Match(context);
    }
  private :
    RegularExp *pAndExp1_;
    RegularExp *pAndExp2_;
};

RegularExp * 
CreateRegularExp(string searchStr)
{
  int len = searchStr.length();
  if (len == 0) return NULL;
  else 
    cout << "===>" << searchStr << endl;

  int pos = searchStr.find_first_of("(&|");
  if (searchStr[pos] == '(') {
    int endParenPos = 0;
    int parenCnt = 1;
    for (int i = pos+1; i < len; i++) {
      if (searchStr[i] == '(') parenCnt++;
      else if (searchStr[i] == ')') parenCnt--;
      else {}

      if (parenCnt == 0) {
        int nextOpPos = searchStr.find_first_of("&|", i+1);
        if (nextOpPos != NA_POS) {
          if (searchStr[nextOpPos] == '&') 
            return new AndExp(CreateRegularExp(searchStr.substr(pos+1,i-pos-1)),
                          CreateRegularExp(searchStr.substr(nextOpPos+1, 
                                                          len-nextOpPos-1)));
          else 
            return new OrExp(CreateRegularExp(searchStr.substr(pos+1,i-pos-1)),
                          CreateRegularExp(searchStr.substr(nextOpPos+1, 
                                                          len-nextOpPos-1)));
        }
        else
          return CreateRegularExp(searchStr.substr(pos+1, i-pos-1));
      }
    }
    // -- searchStr 수식이 잘못된 것임
    return NULL;
  }
  else if (searchStr[pos] == '&') {
    if (pos >= len-1) return NULL;
    return new AndExp(CreateRegularExp(searchStr.substr(0, pos)), 
                  CreateRegularExp(searchStr.substr(pos+1, len-pos-1)));
  }
  else if (searchStr[pos] == '|') {
    if (pos >= len-1) return NULL;
    return new OrExp(CreateRegularExp(searchStr.substr(0, pos)), 
                  CreateRegularExp(searchStr.substr(pos+1, len-pos-1)));
  }
  else {
    // -- 앞뒤 White-space 제거
    string literal;
    strstream strm;
    strm << searchStr;
    strm >> literal;
    if (literal.empty())
      return NULL;

    return new LiteralExp(literal);
  }
}

void
main()
{
  string str;
  getline(cin, str);

  RegularExp *pRegExp = CreateRegularExp(str);
  if (pRegExp == NULL) {
    cout << "Search Pattern Error" << endl;
    exit(0);
  }

  if (pRegExp->Match("data.txt"))
    cout << "Found the search string" << endl;
  else
    cout << "Not Exist the search string" << endl;
}
```
- 색인 객체와 컬렉션 객체가 존재해야 한다.   
- 색인 객체와 컬렉션 객체는 인터페이스와 구현 클래스로 나뉜다.   
- 색인 객체는 컬렉션 객체에 포함되며 종합적인 구조를 띈다.   
- 구현 클래스는 인터페이스를 상속한다.   
- 인터페이스는 순수가상함수로 되어있다.   
