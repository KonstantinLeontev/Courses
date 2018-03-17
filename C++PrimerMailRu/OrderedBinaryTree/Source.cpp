#include <iostream>
#include <string>
#include <sstream>

template<typename T> class Tree {
protected:
	struct Node {
		Node() : m_pLeft(NULL), m_pRight(NULL) {}
		Node(const Node &other) {
			// just copy the key value
			m_Key = other.m_Key;
		}
		~Node() { m_pLeft = NULL; m_pRight = NULL; }

		T m_Key;
		Node *m_pLeft;
		Node *m_pRight;
	};

public:
	Tree() : m_pHead(NULL) {}
	Tree(const Tree &other);
	~Tree() { DeleteTree(m_pHead); }

	void AddElement(const T &newKey);
	void RemoveElement(const T &key);
	Node *FindElement(const T &key) const;
	void ScreenOutput(const int &choice);

	Tree operator+(const Tree &rhs) const;
	Tree operator-(const Tree &rhs) const;
	Tree &operator=(const Tree &rhs);
	template <typename U> friend std::ostream& operator<<(std::ostream &os, const Tree<U> &rhs);

private:
	// recursive function to make the copy constructor work
	void Copy(Node *other);
	// recursive function for AddElement() method
	Node *Insert(Node *curr, const T &newKey);
	// it was part of RemoveElement() at first...
	Node *Find(Node *curr, const T &key) const;
	// this method is a part of next Remove()
	Node *FindMax(Node *curr) const;
	// recursive function to use in public RemoveElement() method
	Node *Remove(Node *curr, const T &key);
	// method delete all the nodes in the tree
	void DeleteTree(Node *curr);
	// output all keys from this tree
	void ReadAllTree(Node *curr);
	// output only non-child leaves
	void ReadNoChild(Node *curr, T firstNonChild);
	// help method for output non-child leaves without comma at the end
	Node *getFirstNonChild(Node *curr);
	// method for '-' operator overloading
	void Subtract(Node *curr, const Tree &rhs, Tree &newTree) const;
	// method for '<<' operator overloading
	void ReadAllToStream(std::ostream &os, Node *curr) const;

	Node *m_pHead;
};

template <typename T> Tree<T>::Tree(const Tree &other) {
	// Delete current tree
	DeleteTree(m_pHead);
	// call recursive function to copy nodes from other tree
	Copy(other.m_pHead);
}

template <typename T>
void Tree<T>::DeleteTree(Node *curr) {
	if (curr != NULL) {
		DeleteTree(curr->m_pLeft);
		DeleteTree(curr->m_pRight);
		delete curr;
	}
}

template <typename T> void Tree<T>::Copy(Node *other) {
	// if there are any nodes for copy
	if (other != NULL) {
		// add current key value to this tree
		AddElement(other->m_Key);
		// then go to the left
		if (other->m_pLeft != NULL) {
			Copy(other->m_pLeft);
		}
		// and go to the right
		if (other->m_pRight != NULL) {
			Copy(other->m_pRight);
		}
	}
}

template <typename T> void Tree<T>::AddElement(const T &newKey) {
	m_pHead = Insert(m_pHead, newKey);
}

template <typename T>
typename Tree<T>::Node* Tree<T>::Insert(Node *curr, const T &newKey) {
	// clear tree case
	if (curr == NULL) {
		Node *newLeaf = new Node;
		newLeaf->m_Key = newKey;
		return newLeaf;
	}
	// if new key is less than current go to left side
	if (curr->m_Key > newKey) {
		curr->m_pLeft = Insert(curr->m_pLeft, newKey);
	}
	// otherwise go to the right
	if (curr->m_Key < newKey) {
		curr->m_pRight = Insert(curr->m_pRight, newKey);
	}
	// after receiving the base case unwind all subtree back and return first head pointer
	return curr;
}

template <typename T>
typename Tree<T>::Node* Tree<T>::FindElement(const T &key) const {
	return Find(m_pHead, key);
}

template <typename T>
typename Tree<T>::Node* Tree<T>::Find(Node *curr, const T &key) const {
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
		return Find(curr->m_pLeft, key);
	}
	// or go to the left side
	else {
		return Find(curr->m_pRight, key);
	}
}

template <typename T>
typename Tree<T>::Node* Tree<T>::FindMax(Node *curr) const {
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
typename Tree<T>::Node* Tree<T>::Remove(Node *curr, const T &key) {
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
		// only left children case
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

template <typename T> void Tree<T>::RemoveElement(const T &key) {
	// use private recursive method, that returns new tree
	m_pHead = Remove(m_pHead, key);
}

template <typename T> void Tree<T>::ReadAllTree(Node *curr) {
	// if there are any nodes in the tree
	if (curr != NULL) {
		ReadAllTree(curr->m_pLeft);
		ReadAllTree(curr->m_pRight);
		std::cout << curr->m_Key << ',';
	}
}

template <typename T>
typename Tree<T>::Node* Tree<T>::getFirstNonChild(Node *curr) {
	if (curr == NULL) {
		return NULL;
	}
	if (curr->m_pLeft == NULL && curr->m_pRight == NULL) {
		return curr;
	}
	else if (curr->m_pLeft != NULL){
		return getFirstNonChild(curr->m_pLeft);
	}
	else {
		return getFirstNonChild(curr->m_pRight);
	}
}

template <typename T> void Tree<T>::ReadNoChild(Node *curr, T firstNonChild) {
	// if there are any nodes in the tree
	if (curr != NULL) {
		// read from left and right
		ReadNoChild(curr->m_pLeft, firstNonChild);
		ReadNoChild(curr->m_pRight, firstNonChild);
		// and output only non-child leaves
		if (curr->m_pLeft == NULL && curr->m_pRight == NULL) {
			// add comma separator after all leaves exept first one
			if (curr->m_Key != firstNonChild) {
				std::cout << ',';
			}
			std::cout << curr->m_Key;
		}
	}
}

template <typename T> void Tree<T>::ScreenOutput(const int &choice) {
	// output all nodes if there are any
	if (choice == 1 && m_pHead != NULL) {
		ReadAllTree(m_pHead);
	}
	// output non-child nodes
	else if (choice == 2 && m_pHead != NULL) {
		Node *p_firstNonChild = getFirstNonChild(m_pHead);
		T firstNonChild = p_firstNonChild->m_Key;
		ReadNoChild(m_pHead, firstNonChild);
	}
}

template <typename T> Tree<T> Tree<T>::operator+(const Tree &rhs) const {
	// new tree for result of addition
	Tree result;
	// uses private method to recursive copy values from rhs to this tree
	result.Copy(rhs.m_pHead);
	// copy lhs values
	result.Copy(m_pHead);
	// return copy of the result tree becouse of ending result lifetime
	return result;
}

template <typename T> void Tree<T>::Subtract(Node *curr, const Tree &rhs, Tree &newTree) const {
	if (curr != NULL) {
		Subtract(curr->m_pLeft, rhs, newTree);
		Subtract(curr->m_pRight, rhs, newTree);
		// if cannot find the same key value on the right
		if (rhs.FindElement(curr->m_Key) == NULL) {
			// add that key to the new tree
			newTree.AddElement(curr->m_Key);
		}
	}
}

template <typename T> Tree<T> Tree<T>::operator-(const Tree &rhs) const {
	// create new tree for result
	Tree result;
	// traverse this tree and check every node for same value in the rhs tree
	Subtract(m_pHead, rhs, result);
	// return copy of new tree
	return result;
}

template <typename T> Tree<T> &Tree<T>::operator=(const Tree &rhs) {
	// check for self-assignment
	if (this == rhs) {
		return this;
	}
	// completely delete old tree
	DeleteTree(m_pHead);
	// copy rhs tree to the left
	Copy(rhs.m_pHead);
	return this;
}

template <typename T> void Tree<T>::ReadAllToStream(std::ostream &os, Node *curr) const {
	if (curr != NULL) {
		// read current key to stream
		os << curr->m_Key << ',';
		// go to the left
		ReadAllToStream(os, curr->m_pLeft);
		// go to the right
		ReadAllToStream(os, curr->m_pRight);
	}
}

template <typename U> std::ostream& operator<< (std::ostream &os, const Tree<U> &rhs) {
	rhs.ReadAllToStream(os, rhs.m_pHead);
	return os;
}

// checks if input string isn't empty
bool checkInput(std::string &input) {
	if (!input.empty()) {
		// check all characters in the input string
		for (int i = 0; i < input.size(); i++) {
			if (!isdigit(input[i]) && input[i] != '.' && input[i] != ' ') {
				return false;
			}
		}
		return true;
	}
	return false;
}

int  main() {
	// create new tree
	Tree<double> tree;
	double n;
	std::string input, temp;
	// get all input from cin
	std::getline(std::cin, input);
	// put input into ss stream
	std::istringstream ss(input);
	// read from istringstream with ',' as delimiter
	while (std::getline(ss, temp, ',')) {
		// check if input isn't empty
		if (checkInput(temp)) {
			// convert temp string into the double value
			n = std::stod(temp);
			// and add it to the tree
			tree.AddElement(n);
		}
	}
	// put non-child leaves to the screen
	tree.ScreenOutput(2);
}