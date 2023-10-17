#include <thread>
#include <atomic>
#include <iostream>
#include <stdint.h>
#include <vector>
std::atomic<uint64_t> buffer;
//uint64_t buffer = 0;
void increment(uint64_t value)
{
  for(uint64_t i = 0; i < value; ++i)	++buffer;
}
int main()
{
  for(;;)
  {
    std::vector<std::thread>thread_pull;
    for(uint8_t i = 0; i < 10; ++i)	thread_pull.push_back(std::thread(increment, 100));
    for(std::thread &it : thread_pull)	it.join();
    if(buffer != 1000)	std::cout << "[!] Buffer: " << buffer << '\n';
    buffer = 0;

  }
  return 0;
}
