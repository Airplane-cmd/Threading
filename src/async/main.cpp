#include <thread>
#include <vector>
#include <chrono>
#include <future>
#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <mutex>
#include <sstream>
std::vector<uint64_t> results;
std::timed_mutex streamMutex;
uint64_t findOdd(uint16_t id, uint64_t start, uint64_t end)
{
  uint64_t sum = 0;
  if(streamMutex.try_lock_for(std::chrono::seconds(1)))
  {
    std::cout << "[" << id << "] started" << '\n';
    streamMutex.unlock();
  }
  for(uint64_t i = start; i < end; ++i)  if(i & 1)  sum += i;
  if(streamMutex.try_lock_for(std::chrono::seconds(1)))
  {
    std::cout << "[" << id << "] finished" << '\n';
    streamMutex.unlock();
  }
  return sum;
}
int main()
{
  std::chrono::time_point start_tp = std::chrono::steady_clock::now();
  uint64_t start = 0, end = (uint64_t)1<<32;

  if(streamMutex.try_lock_for(std::chrono::seconds(1)))
  {
    std::cout << "[!] Odd sum from " << start << " to " << end << '\n';
    streamMutex.unlock();
  }

  std::vector<std::future<uint64_t>> OddFuture_vctr;
  for(uint16_t i = 0; i < 10; ++i)
  {
//    OddFuture_vctr.push_back(std::async(std::launch::deferred, findOdd, i, start, end));
    OddFuture_vctr.push_back(std::async(std::launch::async, findOdd, i, start, end));
    if(streamMutex.try_lock_for(std::chrono::seconds(1)))
    {
      std::cout << "[" << i << "] New iteration for async()\n";
      streamMutex.unlock();
    }
  }

  for(uint16_t i = 0; i < 10; ++i)
  {
    results.push_back(OddFuture_vctr[i].get());
    if(streamMutex.try_lock_for(std::chrono::seconds(1)))
    {
      std::cout << "[!] New iteration for get()\n";
      streamMutex.unlock();
    }
  }
  for(uint64_t i = 0; i < results.size(); ++i)  std::cout << '[' << i << "] Result: " << results[i] << '\n';
  std::chrono::time_point end_tp = std::chrono::steady_clock::now();
  std::chrono::duration<double> duration = end_tp - start_tp;
  std::cout << "[!] Elapsed duration: " << duration.count() << '\n';

  return 0;
}
