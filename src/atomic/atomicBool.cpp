#include <atomic>
#include <iostream>

int main()
{
  std::atomic<bool> x(0);
  std::cout << "[?] Is lock free: " << (x.is_lock_free() ? "True\n" : "False\n");
  std::atomic<bool> y(1);
  x.store(1);
  x.store(y);
  std::cout << "[Y] Value before load:    " << y.load() << '\n';
  std::cout << "[Y] Value after load:     " << y.load() << '\n';
  bool z = x.exchange(0);
  std::cout << "[Z] Value after exchange: " << z << '\n';
  std::cout << "[X] Value after exchange: " << x.load() << '\n';
  return 0;
}
