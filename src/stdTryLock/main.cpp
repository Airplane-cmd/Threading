#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <array>
#include <utility>
#include <string>
#include <stdint.h>
std::pair<uint64_t, uint64_t> sharedValuePair_g(0, 0);
std::array<std::mutex, 2> mutex_vctr;
void haltForSeconds(uint8_t seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
void incrementSharedPair(uint64_t &value, std::mutex &mutex_, const std::string &desc)
{
  for(uint8_t i = 0; i < 10; ++i)
  {
    mutex_.lock();
    ++value;
    std::cout << desc << value << '\n'; 
    mutex_.unlock();
    haltForSeconds(2); 
  }
}
void consumePair()
{
  uint8_t count = 5;
  uint64_t sum = 0;
  for(;;)
  {
    int lockResult = std::try_lock(mutex_vctr[0], mutex_vctr[1]);
    if(lockResult == -1)
    {
      if(sharedValuePair_g.first != 0 && sharedValuePair_g.second != 0)
      {
	--count;
	sum += sharedValuePair_g.first + sharedValuePair_g.second;
	sharedValuePair_g.first = 0;
	sharedValuePair_g.second = 0;
	std::cout << sum << '\n';
      }
      for(std::mutex& it : mutex_vctr)	it.unlock();
      if(count == 0)	break;
    }
  }
}
int main()
{
  for(;;)
  {
    std::vector<std::thread> threads_vctr;
    threads_vctr.push_back(std::thread(incrementSharedPair, std::ref(sharedValuePair_g.first), std::ref(mutex_vctr[0]), "first: "));
    threads_vctr.push_back(std::thread(incrementSharedPair, std::ref(sharedValuePair_g.second), std::ref(mutex_vctr[0]), "second: "));
    threads_vctr.push_back(std::thread(consumePair));
    for(std::thread& it : threads_vctr)
    {
      if(it.joinable())	it.join();
    }
//    std::cout << sharedValue_g << '\n';
//    sharedValue_g = 0;
    return 0;
  }
}

