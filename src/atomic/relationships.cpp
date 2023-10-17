#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>
std::atomic<bool> state_f{0};
std::vector<int64_t> data_vctr;
void consume()
{
	while(!state_f)	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << data_vctr[0] << '\n';
}
void produce()
{
	data_vctr.push_back(3);
	state_f.store(1);
}
int main()
{
	std::vector<std::thread> thread_pull;
	thread_pull.push_back(std::thread(consume));
	thread_pull.push_back(std::thread(produce));
	for(std::thread &it : thread_pull)	it.join();
	return 0;
}
