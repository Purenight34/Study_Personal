#include <iostream>
#include <vector>
#include <set>
using namespace std;

// [개념] Strict Weak Ordering (엄격한 약순서)

//이런 struct 를 선언하고, set에 집어넣으면 비교가 불가능해서 안된다고 한다.
struct CardX {
    int count;
    vector<int> value;
};
//이 경우, 아래 활성화 되어 있는 struct Card 처럼 operator< 를 내부 인자에 대해 정의해주면 가능하다.
//이때, 비교로 쓰이는 함수는 다음 4가지 조건을 만족해야 한다.
//1. 비반사성 (irreflexivity) : 자기 자신 이랑 비교하면 false
//2. 비대칭성 (asymmetry) a < b가 true면 b < a는 거짓
//3. 추이성 (transitivity) a < b 면서 b < c면 a < c
//4. 동등관계의 추이성 (transitivity of equivalence) 아래 isEquivalent 쪽. a가 b랑 동등, b가 c랑 동등하면 a가 c랑 동등해야함

struct Card {
    int count;          // 비교에는 전혀 쓰이지 않는 필드
    vector<int> value;  // 비교 기준이 되는 필드

    bool operator<(const Card& other) const {
        return value < other.value; 
    }
};

// operator<만으로 "동등"을 판단하는 로직을 직접 구현해서 눈으로 확인.
// 그럼 == 연산자를 만들지 않아도, < 연산자 하나로 동등을 표현할 수 있다.
bool isEquivalent(const Card& a, const Card& b)
{
    return !(a < b) && !(b < a);
}

void printCard(const Card& c)
{
    cout << "count=" << c.count << " value={";
    for (size_t i = 0; i < c.value.size(); i++)
        cout << c.value[i] << (i + 1 < c.value.size() ? "," : "");
    cout << "}";
}

int main()
{
    Card a{ 0, {3, 2, 1} };
    Card b{ 1, {3, 2, 1} }; // count만 다르고 value는 a와 동일
    Card c{ 2, {1, 2, 3} }; // value 자체가 다름

    cout << "[1] operator<로 유도한 동등성 비교\n";
    cout << "a vs b (count 다름, value 같음) -> "
         << (isEquivalent(a, b) ? "동등함" : "다름") << "\n"; // 동등함 (count는 무시됨)
    cout << "a vs c (value 다름) -> "
         << (isEquivalent(a, c) ? "동등함" : "다름") << "\n\n"; // 다름

    cout << "[2] set<Card>는 위 동등성 기준으로 중복을 판단한다\n";
    set<Card> cards;
    auto r1 = cards.insert(a);
    auto r2 = cards.insert(b); // a와 "동등"하다고 판단되어 삽입 실패
    auto r3 = cards.insert(c);

    cout << "a 삽입 성공 여부: " << r1.second << "\n";
    cout << "b 삽입 성공 여부: " << r2.second << "  (value가 a와 같아서 무시됨)\n";
    cout << "c 삽입 성공 여부: " << r3.second << "\n\n";

    cout << "[3] 실제로 set에 남아있는 원소들\n";
    for (const Card& card : cards)
    {
        printCard(card);
        cout << "\n";
    }
    // 주목: b(count=1)는 흔적도 없이 사라졌다.
    // operator<가 value만 보기 때문에, set 입장에서 a와 b는 "같은 원소"였다.
    // -> struct에 필드를 여러 개 넣어도, operator<가 일부만 비교하면
    //    나머지 필드는 set/map의 중복 판정에서 통째로 무시된다는 뜻.

    return 0;
}