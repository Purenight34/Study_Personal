#include <iostream>
#include <thread>

using namespace std;
void work()
{
  for(int i = 0; i < 5; i++)
  {
    cout << "Work Thread : " << i << "\n";
  }
}

int main()
{
  thread worker(work);

  for(int i = 0; i < 5; i++)
  {
    std::cout << "Main Thread : " << i << "\n";
  }

  worker.join();
  
  return 0;
}