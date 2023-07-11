#include "stringMultiply.hpp"
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
int main()
{
	srand(time(0));
        int c = 0;
	int count = 4; 
	const auto startTimePoint = std::chrono::high_resolution_clock::now();
	std::vector<std::thread> threads;
        while(c < count)
        {
                int b = 100;//rand() % 300;
                std::string first = "";
                std::string second = "";
                for(int i = 0; i < b; ++i)      first.push_back(char(rand() % 10 + 48));
//                b = rand() % 300;
                for(int i = 0; i < b; ++i)      second.push_back(char(rand() % 10 + 48));
		auto calculate
		{
			[c](const std::string &first, const std::string &second)
			{
				std::string result = multiply(first, second);
                		std::cout << c + 1 << ": " <<  first << " * " << second << " = " << result << '\n';
                		std::cout << std::endl;
			}
		};
		try
		{
			std::cout << "creating a thread" << '\n';
			std::thread thread(calculate, first, second);
			threads.push_back(std::move(thread));
			std::cout << "thread created" << '\n';
//			th.join();
		}
		catch(std::runtime_error &err)
		{
			std::cout << err.what() << '\n';
		}
                ++c;
        }
	for(uint16_t i = 0; i < threads.size(); ++i)	threads[i].join();
	const auto endTimePoint = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime = endTimePoint - startTimePoint;
	std::cout << "took " << elapsedTime.count() << '\n';
        return 0;

}
//single thread execution took 278.877 seconds
//multy thread execution took 115.671 seconds for clang and 103.822 for gcc
