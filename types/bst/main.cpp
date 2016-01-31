#include <BinarySearchTree.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(int argc, char* argv[])
{
  srand(time(NULL));
 
  static size_t MAX_NUM = 1000;
  if (argc > 1) {
    MAX_NUM = atoi(argv[1]);
  } // if
  

  kkoppolu::BinarySearchTree::Tree myTree;
  for (int i = 0; i < MAX_NUM; ++i) {
    int num = rand() % MAX_NUM + 1;
    if (myTree.exists(num) == false) {
      myTree.add(num);
    } // if
  }

  //myTree.visitPreOrder();
  //myTree.visitInOrder();
  //myTree.visitPostOrder();
  //myTree.visitBreadthFirst();

  int num = rand() % MAX_NUM;
  bool exists = myTree.exists(num);
  //if (exists) std::cout << num << " exists" << std::endl;
  //else        std::cout << num << " does not exist" << std::endl;
  //std::cout << "deleting: " << num << std::endl;
  //myTree.deleteVal(num);
  //myTree.visitInOrder();
  //myTree.visitBreadthFirst();

  std:: cout << "My tree height is " << myTree.getHeight()
	     << std::endl;

  std::cout << "My tree is ";
  if (myTree.isBalanced()) {
    std::cout << "BALANCED" << std::endl;
  } else {
    std::cout << "NOT BALANCED" << std::endl;
  }

  myTree.crudeBalance();
  myTree.visitPreOrder();

  std:: cout << "My tree height is " << myTree.getHeight()
	     << std::endl;

  std::cout << "My tree is ";
  if (myTree.isBalanced()) {
    std::cout << "BALANCED" << std::endl;
  } else {
    std::cout << "NOT BALANCED" << std::endl;
  }
  return 0;
}
