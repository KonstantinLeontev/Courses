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
	~OrderedBinaryTree() { delete m_pHead; m_pHead = NULL; }

	void AddElement(const T &newKey);
	bool RemoveElement(const T &key);
	bool FindElement(const T &key);
	void ScreenOutput();

	OrderedBinaryTree operator+(const OrderedBinaryTree &rhs) const;
	OrderedBinaryTree operator-(const OrderedBinaryTree &rhs) const;
	operator=(const OrderedBinaryTree &rhs);
	operator<<(const OrderedBinaryTree &rhs) const;

private:
	// recursive function to make the copy constructor work
	void Copy(Node *curr);
	// recursive function for AddElement() method
	Node *Insert(Node *curr, const T &newKey);


	Node *m_pHead;
};

template <typename T> OrderedBinaryTree<T>::OrderedBinaryTree(const OrderedBinaryTree &other) {
	// call recursive function to copy nodes from other tree
	Copy(m_pHead);
}

template <typename T> void OrederedBinaryTree<T>::Copy(Node *curr) {
	// if there are any nodes for copy
	if (curr != NULL) {
		// add current key value to this tree
		AddElement(curr->m_Key);
		// then go to the left
		if (curr->m_pLeft != NULL) {
			Copy(curr->m_pLeft);
		}
		// and go to the right
		if (curr->m_pRight != NULL) {
			Copy(curr->m_pRight);
		}
	}
}

template <typename T> void OrderedBinaryTree<T>::AddElement(const T &newKey) {
	m_pHead = Insert(m_pHead, newKey);
}

template <typename T>
typename OrderedBinaryTree<T>::Node* OrderedBinaryTree<T>::Insert(Node *curr, const T &newKey) {
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