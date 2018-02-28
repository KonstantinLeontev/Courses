#include <iostream>

template <typename T> struct Node {
	Node() : m_pLeft(NULL), m_pRight(NULL) {}
	Node(const Node &other);
	~Node();

	T m_key;
	Node *m_pLeft;
	Node *m_pRight;
};

template<Node> class OrderedBinaryTree {
public:
	OrderedBinaryTree() : m_pHead(NULL) {}
	OrderedBinaryTree(const OrderedBinaryTree &other);
	~OrderedBinaryTree();

	bool AddElement();
	bool RemoveElement();
	bool FindElement();
	void ScreenOutput();

	OrderedBinaryTree operator+(const OrderedBinaryTree &rhs) const;
	OrderedBinaryTree operator-(const OrderedBinaryTree &rhs) const;
	operator=(const OrderedBinaryTree &rhs);
	operator<<(const OrderedBinaryTree &rhs) const;

private:	
	Node *m_pHead;
};

int  main() {

}