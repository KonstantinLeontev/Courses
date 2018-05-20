#include <iostream>
#include <unordered_set>

struct hasher {
	size_t operator()(const int &a) const {
		return a % 2;
	}
};

int main (int argc, char **argv) {
    std::unordered_set<int, hasher> s;

    for (int i = 0; i < 5; i++) {
        s.insert(i + 1);
    }

    for (auto i : s) {
        std::cout << i << ' ';
    }

    std::cout << '\n';
}
