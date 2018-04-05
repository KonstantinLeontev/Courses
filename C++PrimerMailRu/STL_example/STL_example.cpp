#include <iostream>
#include <vector>

// Print vector to the screen.
void printVector(const std::vector<long int*> &vec) {
	int sizeV = vec.size();
	std::cout << '(' << *(vec[0]);
	for (int i = 1; i < sizeV; i++) {
		std::cout << ',' << *(vec[i]);
	}
	std::cout << ')';
}

void changeSignNext(std::vector<long int*> &vec) {
	for (int i = vec.size() - 1; i > 0; i--) {
		if (*(vec[i - 1]) < 0) {
			// Negate current number;
			*(vec[i]) *= -1;
		}
	}

	// Print vector onto the screen.
	printVector(vec);
}

int main() {
	long int n;
	char temp;
	std::vector<long int*> vec;

	// Read first character from input.
	std::cin >> temp;
	// Read all numbers and dividers.
	while (temp != ')') {
		std::cin >> n >> temp;
		long int *pN = new long int;
		*pN = n;
		vec.push_back(pN);
	}

	// Swap the sign of next negative element in backwards order.
	changeSignNext(vec);
}