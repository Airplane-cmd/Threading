#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <vector>
uint64_t sharedValue = 0;
std::timed_mutex timed_mutex;
void increment(uint64_t index)
{
//  if(timed_mutex.try_lock_for(std::chrono::seconds(2)))
  auto now = std::chrono::steady_clock::now();
  if(timed_mutex.try_lock_until(now + std::chrono::seconds(2)))
  {
    ++sharedValue;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[+] Thread " << index << " entered\n";
    timed_mutex.unlock();
  }
  else std::cout << "[-] Thread " << index << " couldn't enter\n";
}
int main()
{
  std::vector<std::thread> thread_pull;
  for(uint8_t i = 0; i < 2; ++i)	thread_pull.push_back(std::thread(increment, i));
  for(std::thread &it : thread_pull)	it.join();
  std::cout << "Shared value: " << sharedValue << '\n';
  return 0;
}
