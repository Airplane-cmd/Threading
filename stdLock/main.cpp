#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <array>
#include <iostream>
std::mutex m1, m2;
void taskA()
{
  for(;;)
  {
    std::lock(m1, m2);
    std::cout << "first task\n";
    m1.unlock();
    m2.unlock();
  }
}
void taskB()
{
  for(;;)
  {
    std::lock(m2, m1);
    std::cout << "second task\n";
    m2.unlock();
    m1.unlock();
  }
}
int main()
{
  std::thread t1(taskA);
  std::thread t2(taskB);
  t1.join();
  t2.join();
  return 0;
}
    
