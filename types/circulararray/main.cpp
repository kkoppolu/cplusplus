#include <circulararray.h>
#include <iostream>

int main(int argc, char* argv[])
{
  int num(0);
  kkoppolu::CircularArray arr;
  do {
    std::cin >> num;
    if (num > 0)
      arr.add(num);
  } while (num > 0);
  arr.print(std::cout);
  return 0;

}
