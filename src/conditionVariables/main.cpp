#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <condition_variable>
std::condition_variable condVar_g;
std::mutex mutex_g;
std::timed_mutex debugMutex_g;
uint64_t buffer_g = 0;
void increaseBuffer(const uint8_t index, const uint64_t value)
{
  std::lock_guard<std::mutex> lockGuard(mutex_g);
  buffer_g += value;
  if(debugMutex_g.try_lock_for(std::chrono::seconds(1)))
  {
    std::cout << "[+]" <<  ": " << (uint16_t)index << " " << buffer_g << "(" << value <<")" << '\n';
    debugMutex_g.unlock();
  }
  condVar_g.notify_one();
}
void decreaseBuffer(const uint8_t index, const uint64_t value)
{
  for(;;)
  {
    std::unique_lock<std::mutex> uniqueLock(mutex_g);
    condVar_g.wait(uniqueLock, [value]{return buffer_g > value;});//mutex acquired when lambda executed after notify
    if(buffer_g >= value)
    {
      buffer_g -= value;
      if(debugMutex_g.try_lock_for(std::chrono::seconds(1)))
      {
	std::cout << "[-]" <<  ": " << (uint16_t)index << " " << buffer_g << "(" << value <<")" << '\n';
	debugMutex_g.unlock();
      }
      break;
    }
    else
    {
      if(debugMutex_g.try_lock_for(std::chrono::seconds(1)))
      {
	std::cout << "[!] " << (uint16_t)index << '\n';
	debugMutex_g.unlock();
      }
    }
  }
}
int main()
{
  std::vector<std::thread> thread_pull;
  thread_pull.push_back(std::thread(decreaseBuffer, 0, 1500));
  for(uint8_t i = 1; i < 20; ++i)
  {
    thread_pull.push_back(std::thread(increaseBuffer, i, 100));
  }
  for(std::thread &it : thread_pull)	it.join();
  return 0;
}
