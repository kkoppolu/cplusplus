#include <memory>
#include <iostream>
#include <vector>

namespace kkoppolu {
  namespace  BinarySearchTree {

    class Node {
    public:
      Node(int val);
      Node(int                           val,
	   const std::shared_ptr<Node>&  left,
	   const std::shared_ptr<Node>&  right);
	
      int value() const {return d_value;}
      void setValue(int val) {d_value = val;}
      
      std::shared_ptr<const Node> left() const {return d_left;}
      std::shared_ptr<const Node> right() const {return d_right;}
      

    private:
      int d_value;
      std::shared_ptr<Node> d_left;
      std::shared_ptr<Node> d_right;

      std::shared_ptr<Node>& left();
      std::shared_ptr<Node>& right();

      friend class Tree;
    };

    std::ostream& operator<<(std::ostream& os, const Node& node);
    bool operator<(const Node& lhs, const Node& rhs);
    
    class Tree {
    public:
      void visitPreOrder() const;
      void visitInOrder() const;
      void visitPostOrder() const;
      void visitBreadthFirst() const;

      bool isBalanced(void) const;
      bool isBalanced(const std::shared_ptr<Node>&  node) const;
      void crudeBalance();
      int getHeight(void) const;
      
      bool exists(int val) const;
      // add a value
      void add(int val);
      // remove a value/node -
      // will delete the first Node with the value found
      void deleteVal(const Node& val);
      
    private:

      int getHeight(const Node& node) const;
      void balanceBySortedArray(const std::vector<Node>& nodes,
				int start, int end);
      bool doesExist(int val,
		     std::shared_ptr<const Node> p) const;
      
      int retrieveMax(Node& n) const;
      void addHelper(int val, Node& parent);
      std::shared_ptr<Node> deleteHelper(
	int val, std::shared_ptr<Node> parent);
      
      void inOrderVisitor(Node& node) const ;
      void postOrderVisitor(Node& node) const;
      
      std::shared_ptr<Node>  d_root;
    };

  } // BinarySearchTree
} // kkoppolu
