#include <iostream>

template<typename T> class OrderedBinaryTree {
protected:
	struct Node {
		Node() : m_pLeft(NULL), m_pRight(NULL) {}
		Node(const Node &other) {
			// just copy the key value
			m_Key = other.m_key;
			// and don't set pointers for now???
		}
		~Node() { delete m_pLeft; m_pLeft = NULL; delete m_pRight; m_pRight = NULL; }

		T m_key;
		Node *m_pLeft;
		Node *m_pRight;
	};

public:
	OrderedBinaryTree() : m_pHead(NULL) {}
	OrderedBinaryTree(const OrderedBinaryTree &other);
	~OrderedBinaryTree(delete m_pHead; m_pHead = NULL;);

	void AddElement(const T &newKey);
	bool RemoveElement(const T &key);
	bool FindElement(const T &key);
	void ScreenOutput();

	OrderedBinaryTree operator+(const OrderedBinaryTree &rhs) const;
	OrderedBinaryTree operator-(const OrderedBinaryTree &rhs) const;
	operator=(const OrderedBinaryTree &rhs);
	operator<<(const OrderedBinaryTree &rhs) const;

	// just traverse all the tree
	Node* copyTree(const Node &other);

private:
	// recursive function for AddElement() method
	Node *Insert(Node *curr, const T &newKey);

	Node *m_pHead;
};

template <typename T> OrderedBinaryTree<T>::OrderedBinaryTree(const OrderedBinaryTree &other) {
	// if there are any nodes in current object, just delete them
	if (m_pHead != NULL) {
		delete m_pHead;
		m_pHead = NULL;
	}
	// and create new one
	m_pHead = new Node;
	// check if other tree is empty
	if (other.m_pHead != NULL) {
		// read tree and create nodes with corresponding values
		m_pHead->m_Key = other.m_pHead->m_Key;
		while (readTree(other.m_pHead) == true) {
			AddElement();
		}
	}
}

template <typename T> void OrderedBinaryTree<T>::AddElement(const T &newKey) {
	m_pHead = Insert(m_pHead, newKey);
}

template <typename T> OrderedBinaryTree<T>::Insert(Node *curr, const T &newKey) {
	// clear tree case
	if (curr == NULL) {
		Node *newLeaf = new Node;
		newLeaf->m_Key = newKey;
		return newLeaf;
	}
	// if new key is less than current go to left side
	if (curr->m_Key > newKey) {
		curr->m_pLeft = AddElement(curr->m_pLeft, newKey);
	}
	// otherwise go to the right
	else (curr->m_Key < newKey) {
		curr->m_pRight = AddElement(curr->m_pRight, newKey);
	}
	// after receiving the base case unwind all subtree back and return first head pointer
	return curr;
}

template <typename T> OrderedBinaryTree<T>::readTree() {

}

int  main() {

}