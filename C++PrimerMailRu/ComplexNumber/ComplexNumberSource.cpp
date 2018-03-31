#include <iostream>
#include <vector>

template <typename R, typename I>
class Complex {
public:
	Complex() : m_Real(0), m_Imaginary(0) {};
	Complex(const Complex &other);
	~Complex();

	void SetReal(const R &real);
	void SetImaginary(const I &imaginary);

	void Add(const Complex &other);
	void Subtract(const Complex &other);
	void Product(const Complex &other);
	void ScreenOutput() const;

	// Operators overloading TODO.

private:
	R m_Real;
	I m_Imaginary;
};

// Read formatted input to vector.
template <typename R, typename I>
void ReadToVector(std::vector<Complex<R, I>> &vec, Complex<R, I> &cNum, char &temp, int &real, int &imaginary) {
	while (temp != ']') {
		// Read complex numbers as '(' int ',' int ')' ','.
		std::cin >> temp >> real >> temp >> imaginary >> temp >> temp;
		// Assign values to complex number.
		cNum.SetReal(real);
		cNum.SetImaginary(imaginary);
		// Add complex number to the vector.
		vec1.push_back(cNum);
	}
}

template <typename R, typename I>
void AddVectors(
	const std::vector<Complex<R, I>> &vec1,
	const std::vector<Complex<R, I>> &vec2,
	std::vector<Complex<R,I>> &vec3) {
	// TODO
}

template <typename R, typename I>
void PrintVector(std::vector<Complex<R, I>> &vec) {
	// TODO
}

int main() {
	// Number object to save input data.
	Complex<int, int> cNum;
	// Two vectors will be filled from input.
	std::vector<Complex<int, int>> vec1(0), vec2(0), vec3(0);
	// Temp variables for reading from cin.
	int real, imaginary;
	char temp;

	// Read first symbol.
	std::cin >> temp;
	// Read first vector.
	ReadToVector(vec1, cNum, temp, real, imaginary);
	// Read comma and square braquet dividers.
	std::cin >> temp >> temp;
	// Read second vector
	ReadToVector(vec2, cNum, temp, real, imaginary);

	// Add first two vectors together and store result in vec3
	AddVectors(vec1, vec2, vec3);

	// Print vec3 onto screen.
	PrintVector(vec3);
}