#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <stdint.h>
uint64_t sharedValue_g = 0;
std::mutex mutex_;
void incrementSharedValue()
{
  for(uint64_t i = 0; i < (2<<19); ++i)
  {
    mutex_.try_lock();
    ++sharedValue_g;
    mutex_.unlock();
  }
}
int main()
{
  for(;;)
  {
    std::vector<std::thread> threads_vctr;
    for(uint64_t i = 0; i < 2; ++i)
    {
      threads_vctr.push_back(std::thread(incrementSharedValue));
    }
    for(std::thread& it : threads_vctr)
    {
      if(it.joinable())	it.join();
    }
    std::cout << sharedValue_g << '\n';
    sharedValue_g = 0;
    return 0;
  }
}

