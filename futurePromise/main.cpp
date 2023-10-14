#include <thread>
#include <vector>
#include <chrono>
#include <future>
#include <algorithm>
#include <iostream>
#include <stdint.h>
void findOdd(std::promise<uint64_t> &&OddSumPromise, uint64_t start, uint64_t end)
{
  uint64_t sum = 0;
  for(uint64_t i = start; i < end; ++i)  if(i & 1)  sum += i;
  OddSumPromise.set_value(sum);
}
int main()
{
  uint64_t start = 0, end = (uint64_t)1<<63;
  std::cout << "[!] Odd sum from " << start << " to " << end << '\n';
  std::promise<uint64_t> OddSum;
  std::future<uint64_t> OddFuture = OddSum.get_future();
  std::vector<std::thread> thread_pull;
  thread_pull.push_back(std::thread(findOdd, std::move(OddSum), start, end));
  std::cout << "[!] Waiting for result\n";
  std::cout << OddFuture.get() << '\n';
  for(std::thread &it : thread_pull)  it.join();
  return 0;
}
