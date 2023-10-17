#include <atomic>
#include <iostream>
//#include <thread>
#include <stdint.h>
int main()
{
  std::atomic<uint8_t> x{21};
  uint8_t expectedValue = 20;
  std::cout << "[!] Expected value: " << (uint16_t)expectedValue << '\n';
  bool succesOnExchange = x.compare_exchange_weak(expectedValue, 6);
  std::cout << (succesOnExchange ? "[+] " : "[-] ") <<  "Expected: "  <<  (uint16_t)expectedValue << ", " << "Atomic X: " << uint16_t(x.load()) << '\n';
  return 0;
  
}


