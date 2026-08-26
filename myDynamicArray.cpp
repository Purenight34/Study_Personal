#include <iostream>
#include <stdexcept> //예외 던지기 용

// 아래 순서대로 하면 이해하기 좋아요~
// 1. 변수, 함수명 선언
// 2. 생성자, 소멸자 구현
// 3. pushBack, 꽉 안찼을 때 구현
// 4. pushBack, 꽉 찼을 때 구현
// 5. getSize 구현
// 6. get 구현
// 7. pop 구현 
class MyDynamicArray
{
private:
  int* data;
  int size;
  int capacity;

public:
  MyDynamicArray();
  ~MyDynamicArray();

  void pushBack(int value);
  void pop();

  int get(int index);
  int getSize();
};

MyDynamicArray::MyDynamicArray()
{
  size = 0;
  capacity = 2;
  data = new int[capacity];
}

MyDynamicArray::~MyDynamicArray()
{
  delete[] data;
}

void MyDynamicArray::pushBack(int value)
{
  if(size == capacity)
  {
    //새거 만들고
    int newCapacity = capacity * 2;
    int* newData = new int[newCapacity];
    //새 거에 복사하기
    for(int i = 0; i < size; i++)
    {
      newData[i] = data[i];
    }
    //가르키는 객체(배열) 해제하고 바꾸기
    delete[] data;
    data = newData;
    capacity = newCapacity;
  }

  data[size] = value;
  size++;
}

void MyDynamicArray::pop()
{
  if(size > 0)
  {
    size--;
  }
}

int MyDynamicArray::get(int index)
{
  if(index < 0 || index >= size)
  {
    throw std::out_of_range("범위 밖"); //throw는 따로 보기
  }

  return data[index];
  // return *(data + index);
}

int MyDynamicArray::getSize()
{
  return size;
}