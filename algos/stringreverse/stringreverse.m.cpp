#include <iostream>

int main(int argc, char* argv[])
{
  if (argc > 1) {
    std::cout << argv[1] << std::endl;
  } else {
    std::cerr << "Provide a string to reverse" << std::endl;
    return 1;
  }

  // find the end pointer
  int i=0;
  char* str = argv[1];
  
  while (str[i] != 0) {
    ++i;
  }
  int end = i - 1;
  int start = 0;

  while (start < end) {
    char tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    --end;
    ++start;
  }
  std::cout << str << std::endl;
  return 0;
}
