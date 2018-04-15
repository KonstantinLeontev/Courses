#include <iostream>
#include <vector>

// Board output.
void printBoard(std::vector<std::vector<int> > &board, const int &size, int &varCnt) {
	std::cout << "\nSolution " << varCnt << '\n';
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

// Puts queen to the given place and marks others being attacked.
void putQueen(std::vector<std::vector<int> > &board, const int &size, int i, int j) {
	// Mark all squares in the same column.
	for (int k = 0; k < size; k++) {
		board[k][j] = 1;
	}
	// Mark all squares in the same row.
	for (int m = 0; m < size; m++) {
		board[i][m] = 1;
	}

	// Mark diagonals.
	int k = i;
	int m = j;
	// To top-left.
	for (; k >= 0 && m >= 0; k--, m--) {
		board[k][m] = 1;
	}
	// To top-right.
	k = i; m = j;
	for (; k >= 0 && m < size; k--, m++) {
		board[k][m] = 1;
	}
	// To bottom-left.
	k = i; m = j;
	for (; k < size && m >= 0; k++, m--) {
		board[k][m] = 1;
	}
	// To bottom-right.
	k = i; m = j;
	for (; k < size && m < size; k++, m++) {
		board[k][m] = 1;
	}
}

// Finds the number of solutions.
void queenPuzzle(std::vector<std::vector<int> > board, const int &size, int i, int queenCnt, int &varCnt) {
	// Solution case
	if (queenCnt == size) {
		varCnt++;
		queenCnt = 0;
		printBoard(board, size, varCnt);
	}
	// None solution case.
	else if (i != size) {
		for (int j = 0; j < size; j++) {
			if (!board[i][j]) {
				std::vector<std::vector<int> > newBoard;
				newBoard = board;
				putQueen(newBoard, size, i, j);
				// And go to the next line.
				queenPuzzle(newBoard, size, i + 1, queenCnt + 1, varCnt);
			}
		}
	}	
}

int main() {
	bool run = true;
	int size{};

	// Main loop.
	while (run) {
		std::cout << "Input the size of the board (2 - 10) or 0 for quit: ";
		std::cin >> size;
		if (!size) {
			run = false;
		}
		else if (size < 2 || size > 10) {
			"Wrong input! Try again.\n";
		}
		else {
			// Make the array.
			std::vector<std::vector<int> > board(size, std::vector<int> (size, 0));

			// Variant's counter.
			int varCnt = 0;
			// Calculate the number of variants.
			queenPuzzle(board, size, 0, 0, varCnt);

			// Output the quantity of solutions.
			std::cout << varCnt << '\n';
		}
	}
	return 0;
}