#include "../include/five.hpp"
#include <iostream>

int main() {

  Five five1;
  Five five2(4, 2);
  Five five3({1, 3, 2, 4});
  Five five4("1324");

  std::cout << "five1 = " << five1 << "\n";
  std::cout << "five2 = " << five2 << "\n";
  std::cout << "five3 = " << five3 << "\n";
  std::cout << "five4 = " << five4 << "\n";

  Five sum = five3 + five4;
  Five diff = sum - five3;

  std::cout << "five3 + five4 = " << sum << "\n";
  std::cout << "sum - five3 = " << diff << "\n";

  std::cout << "five3 == five4? " << (five3 == five4 ? "yes" : "no")
            << std::endl;
  std::cout << "sum >= diff? " << (sum >= diff ? "yes" : "no") << std::endl;

  Five copy = five3;
  Five moved = std::move(copy);

  std::cout << "copy after move = " << copy << "\n";
  std::cout << "moved = " << moved << "\n";

  return 0;
}