#include <iostream>
#include <atomic>
#include <stdint.h>
int main()
{
  uint16_t buffer[20];
  for(uint8_t i = 0; i < 20; ++i)  buffer[i] = i + 1;
  std::atomic<uint16_t*> buffer_ptr{buffer};

	std::cout << *(buffer_ptr.fetch_add(5))  << " " << *(buffer + 5) << '\n';
	std::cout << *(buffer_ptr) << '\n';
  std::cout << "[?] Is lock free object: " << (buffer_ptr.is_lock_free() ? "True" : "False") << '\n';
  uint16_t *anotherBuffer_ptr = buffer_ptr.fetch_add(5);
  buffer_ptr.store(anotherBuffer_ptr);
  std::cout << "[~] Value referencing to by pointer: " << (uint16_t)*(buffer_ptr.load()) << '\n';
  bool succesOnExchange = buffer_ptr.compare_exchange_weak(anotherBuffer_ptr, buffer + 10);
	std::cout << (succesOnExchange ? "[+]" : "[-]") << "Buffer value: " << (uint16_t)*buffer_ptr << '\n';

	return 0;
}
