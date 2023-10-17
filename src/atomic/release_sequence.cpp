#include <atomic>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <stdint.h>
#include <assert.h>
std::atomic<int64_t> count{0};
std::queue<int64_t> dataQueue;
std::queue<int64_t> queue;
void populateQueue()
{
	for(uint64_t i = 0; i < 2000; ++i)	dataQueue.push(i);

	count.store(2000, std::memory_order_release);

	std::cout << count.load(std::memory_order_acquire) << ' ' << dataQueue.size() << '\n';
}
void readQueue(uint16_t id)
{
	std::cout << id << '\n';
	for(;;)
	{
		int64_t index = 0;
		if((index = count.fetch_sub(1, std::memory_order_acquire)) >= -1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			std::cout << id << ' ' << count.load(std::memory_order_acquire) << ' ' << dataQueue.front() << '\n';
			queue.push(dataQueue.front());
			if(dataQueue.front() == 1999)	break;
			dataQueue.pop();
		}
		else	continue;
		
	}
}
int main()
{
	std::chrono::time_point start = std::chrono::high_resolution_clock::now();
	std::vector<std::thread> thread_pull;
	thread_pull.push_back(std::thread(populateQueue));
//	thread_pull.push_back(std::thread(readQueue, 1));
	for(uint8_t i = 0; i < 4; ++i)	thread_pull.push_back(std::thread(readQueue, i));
	for(std::thread &it : thread_pull)	it.join();
	std::chrono::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	while(!queue.empty())
	{
		std::cout << queue.front() << '\n';
		queue.pop();
	}
	std::cout << "Duration: " << std::chrono::duration<double>(end - start).count() << '\n';
	return 0;
}
