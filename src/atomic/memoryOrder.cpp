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
	x.store(1, std::memory_order_seq_cst);
}
void writeB()
{
	y.store(1, std::memory_order_seq_cst);
}
void sequentialReadA()
{
	while(!x.load(std::memory_order_seq_cst))	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	if(y.load(std::memory_order_seq_cst))	z++;
}
void sequentialReadB()
{
	while(!y.load(std::memory_order_seq_cst))	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	if(x.load(std::memory_order_seq_cst))	z++;
}
int main()
{
	for(;;)
	{
		x.store(0);
		y.store(0);
		z.store(0);
		std::vector<std::thread> thread_pull;
		thread_pull.push_back(std::thread(writeA));
		thread_pull.push_back(std::thread(writeB));
		thread_pull.push_back(std::thread(sequentialReadA));
		thread_pull.push_back(std::thread(sequentialReadB));
		for(std::thread &it : thread_pull)	it.join();
		
		if(z != 2 || 1)	std::cout << z.load() << '\n';//assert(z == 2);
	}
		return 0;
}
