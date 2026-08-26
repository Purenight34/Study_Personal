#include <iostream>
#include <stdexcept>

class MyQueue
{
private :
  int* data;
  int index;
  int size;

public :
  MyQueue(int queueSize);
  ~MyQueue();
  void pushBack(int value);
  int pop();
};

MyQueue::MyQueue(int queueSize)
{
  size = queueSize;
  data = new int[size];
  index = 0;
}

MyQueue::~MyQueue()
{
  delete[] data;
}

void MyQueue::pushBack(int value)
{
  if(index >= size)
  {
    throw std::out_of_range("범위 밖");
  }
  data[index] = value;
  index++;
}

int MyQueue::pop()
{
  if(index == 0)
  {
    throw std::out_of_range("범위 밖");
  }
  
  int result = data[index];
  for(int i = 0; i < index - 1; i++)
  {
    data[i]= data[i+1];
  }
  index--;
  return data[index];
}