#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <vector>
#include <array>
std::array<std::mutex, 2> mutex_arr;
void threadFunction()
{
  mutex_arr[0].lock();
  mutex_arr[1].lock();
  std::cout << "First thread\n";
  mutex_arr[0].unlock();
  mutex_arr[1].unlock();
}
void anotherThreadFunction()
{
  mutex_arr[1].lock();
  mutex_arr[0].lock();
  std::cout << "Second thread\n";
  mutex_arr[1].unlock();
  mutex_arr[0].unlock();
}
int main()
{
  std::thread threadOne(threadFunction);
  std::thread threadTwo(anotherThreadFunction);
  threadOne.join();
  threadTwo.join();
  return 0;
}
