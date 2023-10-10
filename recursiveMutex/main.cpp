#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
std::recursive_mutex mutex_g;
uint64_t buffer_g;
void recursiveFunction(const uint8_t index, const int64_t recursionDepth)
{
  int64_t counter = recursionDepth - 1;
  if(counter < 0)  return;
  mutex_g.lock();
  std::cout << (uint16_t)index << ": " << counter << " " << ++buffer_g << '\n';
  recursiveFunction(index, counter);
  mutex_g.unlock();
}
int main()
{
  std::vector<std::thread> thread_pull;
  for(uint16_t i = 0; i < 5; ++i)
  {
    thread_pull.push_back(std::thread(recursiveFunction, i, 1<<17));
  }
  for(std::thread &it : thread_pull)	it.join();
  return 0;
}
