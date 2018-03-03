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
	// it was part of RemoveElement() at first...
	Node *Find(Node *curr, const T &key);
	// this method is a part of next Remove()
	Node *FindMax(Node *curr);
	// recursive function to use in public RemoveElement() method
	Node *Remove(Node *curr, const T &key);

	Node *m_pHead;
};

template <typename T> OrderedBinaryTree<T>::OrderedBinaryTree(const OrderedBinaryTree &other) {
	// call recursive function to copy nodes from other tree
	Copy(m_pHead);
}

template <typename T> void OrderedBinaryTree<T>::Copy(Node *curr) {
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

template <typename T>
typename OrderedBinaryTree<T>::Node* OrderedBinaryTree<T>::Find(Node *curr, const T &key) {
	// base case for empty tree
	if (curr == NULL) {
		return NULL;
	}
	// if the key is found
	else if (curr->m_Key == key) {
		return curr;
	}
	// otherwise go to the left
	else if (curr->m_Key > key) {
		curr = Find(curr->m_pLeft, key);
	}
	// or go to the left side
	else {
		curr = Find(curr->m_pRight, key);
	}
}

template <typename T>
typename OrderedBinaryTree<T>::Node* OrderedBinaryTree<T>::FindMax(Node *curr) {
	if (curr == NULL) {
		return NULL;
	}
	// check only right side
	if (curr->m_pRight == NULL) {
		return curr;
	}
	return FindMax(curr->m_pRight);
}

template <typename T>
typename OrderedBinaryTree<T>::Node* OrderedBinaryTree<T>::Remove(Node *curr, const T &key) {
	// base case for empty tree
	if (curr == NULL) {
		return NULL;
	}
	// if key is found
	else if (curr->m_Key == key) {
		// there are not any left children
		if (curr->m_pLeft == NULL) {
			Node *temp = curr->m_pRight;
			delete curr;
			return temp;
		}
		// only right children case
		if (curr->m_pRight == NULL) {
			Node *temp = curr->m_pLeft;
			delete curr;
			return temp;
		}
		// otherwise find max value on the left
		Node *maxNode = FindMax(curr->m_pLeft);
		// point max to the left subtree
		maxNode->m_pLeft = curr->m_pLeft;
		// point max to the right subtree
		maxNode->m_pRight = curr->m_pRight;
		// it's time to delete current node
		delete curr;
		curr = NULL;
		return maxNode;
	}
	// go to the left
	else if (curr->m_Key > key) {
		curr->m_pLeft = Remove(curr->m_pLeft, key);
	}
	// otherwise go to the right
	else {
		curr->m_pRight = Remove(curr->m_pRight, key);
	}
	return curr;
}

template <typename T> bool OrderedBinaryTree<T>::RemoveElement(const T &key) {
	// use private recursive method, that returns new tree
	m_pHead = Remove(m_pHead, curr);
}

template <typename T> OrderedBinaryTree<T>::readTree() {

}

int  main() {

}