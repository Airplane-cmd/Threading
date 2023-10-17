#include <atomic>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <stdint.h>
#include <assert.h>
struct X
{
	uint64_t i;
	std::string str;
};
std::atomic<X*> X_ptr;
std::atomic<uint64_t> vl;
void initX()
{
	X *x = new X;
	x->i = 42;
	x->str = "nice";

	vl.store(20, std::memory_order_relaxed);
	X_ptr.store(x, std::memory_order_release);
}
void useX()
{
	X *x;
	while(!(x = X_ptr.load(std::memory_order_consume)));
	assert(x->i == 42);
	assert(x->str == "nice");
	assert(vl.load(std::memory_order_relaxed) == 20);
}
int main()
{
	std::vector<std::thread> thread_pull;
	thread_pull.push_back(std::thread(initX));
	thread_pull.push_back(std::thread(useX));
	for(std::thread &it : thread_pull)	it.join();
	return 0;
}
