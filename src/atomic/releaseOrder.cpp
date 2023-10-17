#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <stdint.h>
#include <assert.h>
std::atomic<bool> x, y;
std::atomic<uint64_t> z;
void writeA()
{
	x.store(1, std::memory_order_release);
}

void writeB()
{
	y.store(1, std::memory_order_release);
}
void readA()
{
	while(!x.load(std::memory_order_acquire));
	if(y.load(std::memory_order_acquire))	z++;
}
void readB()
{
	while(!y.load(std::memory_order_acquire));
	if(x.load(std::memory_order_acquire))	z++;
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
		thread_pull.push_back(std::thread(writeA));
		thread_pull.push_back(std::thread(writeB));
		thread_pull.push_back(std::thread(readA));
		thread_pull.push_back(std::thread(readB));
		for(std::thread &it : thread_pull)	it.join();
		assert(z != 0);
		std::cout << z << ' ';
	}
	return 0;
}
