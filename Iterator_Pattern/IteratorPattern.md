반복자 패턴 (Iterator Pattern)   
=============      
## 반복자 패턴 사용 이유   
데이터 집합은 단순히 1차원배열만 있지 않고, 2차원 배열, 더 나아가 가지에 가지를 뻗는 트리라는 형태의 데이터집합도 존재한다. 데이터를 사용하기 위해서는 해당 데이터 집합에서 요소를 추출해야한다. 초보단계에서는 집합이라 해봤자 1차원배열 혹은 2차원 배열만 존재하여 단순히 인덱스[]연산자를 이용해 순회하면서 데이터 요소들을 추출할 수 있다.  하지만 고급단계로 올라가면 트리라는 형태의 데이터 집합은 어떻게 해야할까? 
> 먼저 배열처럼 요소를 뽑아주는 역할이 없으니 그것부터 만들면 된다.
   
그렇게 해서 요소를 뽑아주는 역할을 가진 객체를 만들었다. 그런데 해당 객체가 어떻게 트리 데이터 집합을 순회하여 요소를 추출해야할까? 그리고 배열들처럼 단순하게 순차적으로만 순회할까? 그렇지도 않다.   
> 따라서 해당 객체를 만들 때는 데이터 집합을 순회하는 알고리즘들의 다양성을 고려하여 해당 객체가 어떤 알고리즘이라도 적용될 수 있게 만든다.   

- 요약
  - 반복자 패턴이란 디자인 패턴 중 행동 패턴으로 여러 데이터 집합 즉, 자료구조를 선회하며 요소를 추출할 수 있는 객체를 만드는 패턴으로 데이터 집합 순회 알고리즘하고 분리되어 있어, 다양한 순회 알고리즘들을 사용하고 해제할 수 있다.
  - 해당 특성 덕분에 하나의 데이터 집합에서 요소를 추출할 때 동시에 다른 순회 알고리즘을 이용해 데이터 요소를 추출할 수 있다.  

-------------
## 예제소스로 반복자 분석   
- 오픈 소스 파일 링크 :    
   https://github.com/minwn3318/Designed_Pattern/blob/main/Iterator_Pattern/Iterator_PatternOpen.md
- 참조용 :   
  https://github.com/JakubVojvoda/design-patterns-cpp/blob/master/iterator/Iterator.cpp
  
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
- 전체흐름   
   - RegularExp : 모든 종류의 정규 표현식의 기본 클래스이다. 반복자를 구현하는 가상 클래스이다.   
   - LiteralExp : 글자 그대로의 문자열 일치를 나타내는 클래스다. 반복자에 해당된다   
   - OrExp : 두 정규 표현식 간의 논리 OR (|) 연산을 나타내는 클래스다. 반복자에 해당된다
   - AndExp : 목적: 두 정규 표현식 간의 논리 AND (&) 연산을 나타내는 클래스다. 반복자에 해당된다  
   - CreateRegularExp 함수:  제공된 검색 문자열을 기반으로 정규 표현식 객체를 생성하는 함수다.

- main 함수
   - 사용자로부터 검색 문자열을 읽어 정규 표현식 객체를 만들고 이를 파일("data.txt")과 테스트한다.   
     1. 사용자로부터 검색 문자열을 읽는다.
     2. CreateRegularExp를 호출하여 정규 표현식 객체를 만든다.
     3. Match 함수를 사용하여 "data.txt"의 내용과 정규 표현식을 테스트한다.
     4. 검색 문자열이 찾아졌는지 여부를 출력합니다.
