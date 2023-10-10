#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <iostream>
std::mutex mutex_g;
uint64_t buffer_g;
void iterativeFunction(uint8_t index, uint64_t iterationCount)
{
  std::unique_lock<std::mutex> lock(mutex_g, std::defer_lock);//automaically calls lock on mutex_g
  lock.lock();
  for(uint64_t i = 0; i < iterationCount; ++i)
  {
    std::cout << (uint16_t)index << ": " << ++buffer_g << '\n';
  }
}
int main()
{
  std::vector<std::thread> thread_pull;
  for(uint64_t i = 0; i < 2; ++i)
  {
    thread_pull.push_back(std::thread(iterativeFunction, i, 10));
  }
  for(std::thread &it : thread_pull)	it.join();
  return 0;
}
