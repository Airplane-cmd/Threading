#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <array>
#include <stdint.h>
#include <assert.h>
std::atomic<bool> x{0}, y{0};
std::array<std::atomic<int64_t>, 5> data;
void populateDataArr()
{
	int64_t start = 43;
	for(uint8_t i = 0; i < 5; ++i)
	{
		data[i].store(start, std::memory_order_relaxed);
		start = start + 2;
		
	}
	x.store(1, std::memory_order_release);
}
void assertion()
{
	while(!y.load(std::memory_order_acquire));
	uint8_t start = 43;
	for(uint8_t i = 0; i < 5; ++i)
	{
		assert(data[i].load(std::memory_order_relaxed) == start);
		start += 2;
	}
}
void sync()
{
	while(!x.load(std::memory_order_acquire));
	y.store(1, std::memory_order_release);
}
int main()
{
	uint64_t counter;
	std::vector<std::thread> thread_pull;
	thread_pull.push_back(std::thread(populateDataArr));
	thread_pull.push_back(std::thread(sync));
	thread_pull.push_back(std::thread(assertion));
	for(std::thread &it : thread_pull)	it.join();
	return 0;
}
