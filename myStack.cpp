#include <iostream>
#include <stdexcept>

// 아래 순서대로 만들어보기
// 1. 필요한 변수, 함수 선언
// 2. 생성자, 소멸자 구현
// 3. isEmpty() 구현
// 4. push 구현
// 5. pop 구현(여기서는 반환까지 함)
class MyStack
{
private :
  int* data;
  int maxSize;
  int top;

public :
  MyStack(int stackSize = 5);
  ~MyStack();
  void push(int value);
  int pop();
  bool isEmpty() const;
};

MyStack::MyStack(int stackSize)
{
  maxSize = stackSize;
  data = new int[maxSize];
  top = -1;
}

MyStack::~MyStack()
{
  delete[] data;
}

void MyStack::push(int value)
{
  if(top + 1 >= maxSize)
  {
    throw std::out_of_range("범위 밖");
  }
  top++;
  data[top] = value;
}

int MyStack::pop()
{
  if(top == -1)
  {
    throw std::out_of_range("범위 밖");
  }
  int temp = data[top];
  top--;
  return temp;
}

bool MyStack::isEmpty() const
{
  return (top == -1);
}