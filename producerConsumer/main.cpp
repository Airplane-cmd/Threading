#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <deque>
#include <stdint.h>
std::condition_variable condVar;
std::mutex mutex_g;
std::deque<uint64_t> buffer;
const uint8_t maxSize = 50;
void produce(uint16_t value)
{
  while(value)
  {
    std::unique_lock<std::mutex> lock(mutex_g);
    condVar.wait(lock, []{return buffer.size() < maxSize;});
    buffer.push_back(value);
    std::cout << "[+] Produced: " << value << '\n';
    --value;
    lock.unlock();
    condVar.notify_one();
  }
}
void consume()
{
  for(;;)
  {
    std::unique_lock<std::mutex> lock(mutex_g);
    condVar.wait(lock, []{return buffer.size() > 0;});
    std::cout << "[-] Consumed: " << buffer.back() << '\n';
    buffer.pop_back();
    lock.unlock();
    condVar.notify_one();
  }
}
int main()
{
  std::vector<std::thread> thread_pull;
  
  thread_pull.push_back(std::thread(consume));
  for(uint8_t i = 0; i < 1; ++i)  thread_pull.push_back(std::thread(produce, 100));
  for(std::thread &it : thread_pull)  it.join();
  return 0;
}
