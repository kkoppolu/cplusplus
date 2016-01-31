#include <sharedpointer.h>

int main(int argc, char* argv[])
{
  using namespace kkoppolu;
  {
    SharedPtr<int> one(new int(1));    
    SharedPtr<int> copyOne(one);    
    SharedPtr<int> assignOne = copyOne;
    SharedPtr<int> two(new int(2));
    SharedPtr<int> twoToOne = assignOne;
    SharedPtr<int> three(new int(3));

    std::cout << *one << std::endl;
    std::cout << *assignOne << std::endl;
    std::cout << *copyOne << std::endl;
    std::cout << *(two.get()) << std::endl;
    std::cout << *twoToOne << std::endl;
    std::cout << *three << std::endl;     
  }
  
  return 0;
}
