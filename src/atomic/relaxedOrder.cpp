#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <stdint.h>
#include <assert.h>
std::atomic<bool> x, y;
std::atomic<uint64_t> z;
void sequentialWrite()
{
	x.store(1, std::memory_order_relaxed);
	y.store(1, std::memory_order_relaxed);
}
void sequentialRead()
{
	while(!y.load(std::memory_order_relaxed));
	if(x.load(std::memory_order_relaxed))	z++;
}
int main()
{
	uint64_t counter;
	for(;;)
	{
		
		x.store(0);
		y.store(0);
		z.store(0);
		std::vector<std::thread> thread_pull;
		thread_pull.push_back(std::thread(sequentialWrite));
		thread_pull.push_back(std::thread(sequentialRead));
		for(std::thread &it : thread_pull)	it.join();
		assert(z != 0);
		std::cout << z << ' ';
	}
	return 0;
}
