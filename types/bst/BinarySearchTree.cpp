#include <BinarySearchTree.h>
#include <stack>
#include <queue>
#include <algorithm>

namespace kkoppolu {
  namespace BinarySearchTree {

    namespace {
      using namespace kkoppolu;
      
      void
      appendNode(std::vector<BinarySearchTree::Node>& nodes,
		 const BinarySearchTree::Node& node)
      {
	nodes.push_back(node);
	if (node.left().get() != NULL) {
	  appendNode(nodes, *node.left());
	}
	if (node.right().get() != NULL) {
	  appendNode(nodes, *node.right());
	}
      } // appendNode
      
    } // namespace

    Node::Node(int val)
      :d_value(val)
    {}

    Node::Node(int                           val,
	       const std::shared_ptr<Node>&  left,
	       const std::shared_ptr<Node>&  right)
      :d_value(val), d_left(left), d_right(right)
    {}

    std::shared_ptr<Node>&    
    Node::left()
    {
      return d_left;
    }

    std::shared_ptr<Node>&    
    Node::right()
    {
      return d_right;
    }

    std::ostream&
    operator<<(std::ostream& os, const Node& node)
    {
      if (os.bad()) {
	return os;
      } // if

      os << node.value() << std::endl;
      return os;
    }

    bool
    operator<(const Node& lhs, const Node& rhs)
    {
      return lhs.value() < rhs.value();
    }

    void
    Tree::addHelper(int val, Node& parent)
    {
      // we need to add to the left of the parent
      if (val < parent.value()) {
	// if there is already a left, move down
	const std::shared_ptr<Node>& left = parent.left();
	if (left.get() != NULL) {
	  addHelper(val, *left);
	} else {
	  // create the node and assign left
	  parent.left() = std::shared_ptr<Node>(new Node(val));
	} // if
      } else {
	// adding to the right
	const std::shared_ptr<Node>& right = parent.right();
	if (right.get() != NULL) {
	  // if right already exists, move down
	  addHelper(val, *right);
	} else {
	  // create the node and assign right
	  parent.right() = std::make_shared<Node>(val);
	} // if
      } // if
    }

    bool
    Tree::exists(int val) const
    {
      if (d_root.get() == NULL) {
	return false;
      } // if

      return doesExist(val, d_root);
    }

    bool
    Tree::doesExist(int val, std::shared_ptr<const Node> p) const
    {
      if (p->value() == val) {
	return true;
      } // if

      if (val < p->value()) {
	if (p->left().get() != NULL) {
	  return doesExist(val, p->left());
	} // if
      } else if (val > p->value()) {
	if (p->right().get() != NULL) {
	  return doesExist(val, p->right());
	} // if
      } // if

      return false;
    } // doesExist

    
    void
    Tree::add(int val)
    {
      if (d_root.get() == NULL) {
	d_root = std::shared_ptr<Node>(new Node(val));
      } else {
	addHelper(val, *d_root);
      } // if
    } // add

    int
    Tree::retrieveMax(Node& n) const
    {
      if (n.right().get() != NULL) {
	return retrieveMax(*(n.right()));
      }

      return n.value();
    }

    std::shared_ptr<Node>
    Tree::deleteHelper(int val, std::shared_ptr<Node> p)
    {
      if (p.get() == NULL) {
	return p;
      } // if
      
      if (val < p->value()) {
	p->left() = deleteHelper(val, p->left());
      } else if (val > p->value()) {
	p->right() = deleteHelper(val, p->right());
      } else {
	// return the non-null child
	if (p->left() == NULL) {
	  return p->right();
	} else if (p->right() == NULL) {
	  return p->left();
	} else {
	  // there are 2 non NULL children. we need to perform a merge here to avoid sub tree formation
	  // we find the max from the left sub-tree and swap it into the position to be deleted
	  // and then delete the swapped position

	  // get data from the rightmost node in the left subtree
	  int max = retrieveMax(*(p->left()));
	  p->setValue(max);
	  // at this point both the current node and the rightmost
	  // node in the left subtree have the same data value

	  // delete the rightmost node in the left subtree
	  p->left() =  deleteHelper(p->value(), p->left()) ;
	} // if
  
      } // if
      return p;
    } // deleteHelper

    
    void
    Tree::deleteVal(const Node& val)
    {
      if(d_root.get() == NULL) {
	return;
      }

      d_root = deleteHelper(val.value(), d_root);
    }

   
    
    void
    Tree::visitPreOrder() const
    {
      if (d_root.get() != NULL) {
	std::cout << "PreOrder(VLR)" << std::endl;
	// VLR
	std::stack<std::shared_ptr<Node> > toVisit;
	if (d_root.get() != NULL) {
	  toVisit.push(d_root);
	} // if
	while (toVisit.empty() == false) {
	  std::shared_ptr<Node> n = toVisit.top();
	  toVisit.pop();
	  if (n.get() == NULL) {
	    break;
	  } // if  
	  // print!
	  std::cout << *n;

	  // we will have to visit right last
	  if (n->right().get() != NULL) {
	    toVisit.push(n->right());
	  } // if
	  // and left now
	  if (n->left().get() != NULL) {
	    toVisit.push(n->left());
	  } // if
	} // while 
      } else {
	std::cout << "EMPTY TREE" << std::endl;
      } // if
    } // visitPreOrder

    void
    Tree::visitPostOrder() const
    {
      if (d_root.get() != NULL) {
	std::cout << "PostOrder(LRV)" << std::endl;
	// LRV
	postOrderVisitor(*d_root);
      } else {
	std::cout << "EMPTY TREE" << std::endl;
      } // if
    } // visitPostOrder

    void
    Tree::visitInOrder() const
    {
      if (d_root.get() != NULL) {
	std::cout << "InOrder(LVR)" << std::endl;
	// LVR
	inOrderVisitor(*d_root);
      } else {
	std::cout << "EMPTY TREE" << std::endl;
      } // if
    } // visitInOrder

    void
    Tree::visitBreadthFirst() const
    {
      std::cout << "BREADTH FIRST" << std::endl;
      if (d_root.get() == NULL) {
	std::cout << "EMPTY TREE" << std::endl;
	return;
      } // if

      std::queue<std::shared_ptr<Node> > toVisit;
      toVisit.push(d_root);
      while (toVisit.empty() == false) {
	// print the queue elements 1 by 1	
	std::shared_ptr<Node>& n = toVisit.front();	  
	if (n.get() != NULL) {
	  std::cout << *n;
	} // if
	toVisit.pop();
	// add its children to the end of the queue
	if (n->left() != NULL) {
	  toVisit.push(n->left());
	} // if
	if (n->right() != NULL) {
	  toVisit.push(n->right());
	} // if
      } // while
    } // visitBreadthFirst

    
    void
    Tree::inOrderVisitor(Node& node) const
    {
      if (node.left().get() != NULL) {
	inOrderVisitor(*(node.left()));
      } // if
      std::cout << node;
      if (node.right().get() != NULL) {
	inOrderVisitor(*(node.right()));
      } // if
    } // inOrderVisitor

    void
    Tree::postOrderVisitor(Node& node) const
    {
      if (node.left().get() != NULL) {
	postOrderVisitor(*(node.left()));
      } // if
      if (node.right().get() != NULL) {
	postOrderVisitor(*(node.right()));
      } // if

      std::cout << node;
    } // inOrderVisitor

    int
    Tree::getHeight(const Node& node) const
    {
      int myHeight = 1;
      int myLHeight = 0;
      if (node.left().get() != NULL) {
	myLHeight = getHeight(*node.left());
      } // if

      int myRHeight = 0;
      if (node.right().get() != NULL) {
	myRHeight = getHeight(*node.right());
      } // if

      myHeight += std::max(myLHeight, myRHeight);

      return myHeight;
    } // getHeight

    
    int
    Tree::getHeight() const
    {
      if (d_root == NULL) {
	return 0;
      } // if
      return getHeight(*d_root);
    } // getHeight

    bool
    Tree::isBalanced(const std::shared_ptr<Node>&  node) const
    {
      if (node == NULL) {
	return true;
      }

      // get the left tree height
      int lH = 0;
      if (node->left().get() != NULL) {
	lH = getHeight(*(node->left()));
      } // if

      // get the right tree height
      int rH = 0;
      if (node->right().get() != NULL) {
	rH = getHeight(*(node->right()));
      } // if

      // if they are off by more than 1, they are not
      // balanced
      if (std::abs(rH - lH) <= 1
	  && isBalanced(node->left())
	  && isBalanced(node->right())) {
	return true;
      }
      return false;
    }

    
    bool
    Tree::isBalanced() const
    {
      return isBalanced(d_root);
    }


    void
    Tree::balanceBySortedArray(const std::vector<Node>& nodes,
			       int start, int end)
    {
      if (start > end) {
	return;
      } // if
      
      // keep on adding the middle node
      size_t mid = (start + end)/2;
      add(nodes[mid].value());

      // do it for the left half
      balanceBySortedArray(nodes, start, mid - 1);

      // do it for the right half
      balanceBySortedArray(nodes, mid + 1, end);
    }

    
    void
    Tree::crudeBalance()
    {
      if (d_root.get() == NULL) {
	return;
      } // if
      std::vector<Node> nodes;
      appendNode(nodes, *d_root);

      
      std::sort(nodes.begin(), nodes.end());
      for (size_t i = 0; i < nodes.size(); ++i) {
	deleteVal(nodes[i].value());
      } // for

      balanceBySortedArray(nodes, 0, nodes.size() - 1);
    }         
      
    
  } // BinarySearchTree
} // kkoppolu
 
