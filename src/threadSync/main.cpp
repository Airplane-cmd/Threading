#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <vector>
#include <stdint.h>
uint64_t buffer_g = 0;
void increaseBuffer(const uint64_t value)
{
  buffer_g += value;
}
int main()
{
  for(;;)
  {
    std::vector<std::thread> thread_pull;
    for(uint8_t i = 0; i < 2; ++i)
    {
      thread_pull.push_back(std::thread(increaseBuffer, 100 * (i + 1)));
    }
    for(std::thread &it : thread_pull)	it.join();
    if(buffer_g != 300)	std::cout << buffer_g << '\n';
    buffer_g = 0;
  }
  return 0;
}
