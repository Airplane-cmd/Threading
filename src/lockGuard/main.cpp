#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
std::mutex mutex_g;
uint64_t buffer_g;
void iterativeFunction(const uint8_t index, const int64_t iterationCount)
{
  for(uint64_t i = 0; i < iterationCount; ++i)
  {
    std::lock_guard<std::mutex> lock(mutex_g);
    std::cout << (uint16_t)index << ": " << ++buffer_g << '\n';
  }
}
int main()
{
  std::vector<std::thread> thread_pull;
  for(uint16_t i = 0; i < 5; ++i)
  {
    thread_pull.push_back(std::thread(iterativeFunction, i, 1<<20));
  }
  for(std::thread &it : thread_pull)	it.join();
  return 0;
}
