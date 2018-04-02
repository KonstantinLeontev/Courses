#include <iostream>
#include <vector>

template <typename R, typename I>
class Complex {
public:
	Complex() : m_Real{}, m_Imaginary{} {} // Value initialization (since C++ 11).
	Complex(R real, I imaginary) : m_Real(real), m_Imaginary(imaginary){} // With arguments.
	Complex(const Complex &rhs) : m_Real(rhs.m_Real), m_Imaginary(rhs.m_Imaginary) {}
	~Complex() {}

	void SetReal(const R &real) { m_Real = real; }
	void SetImaginary(const I &imaginary) { m_Imaginary = imaginary; }

	Complex Add(const Complex &rhs) { m_Real += rhs.m_Real; m_Imaginary += rhs.m_Imaginary; }
	Complex Subtract(const Complex &rhs) { m_Real -= rhs.m_Real; m_Imaginary -= rhs.m_Imaginary; }
	Complex Product(const Complex &rhs) { m_Real *= rhs.m_Real; m_Imaginary *= rhs.m_Imaginary; }
	void ScreenOutput() const;

	// Operators overloading
	Complex operator+(const Complex &rhs);
	Complex operator-(const Complex &rhs);
	Complex operator*(const Complex &rhs);
	Complex& operator=(const Complex &rhs);
	template <typename V, typename W> friend std::ostream& operator<<(std::ostream &os, const Complex<V, W> &rhs);

private:
	R m_Real;
	I m_Imaginary;
};

template <typename R, typename I>
Complex<R, I> Complex<R, I>::operator+(const Complex &rhs) {
	// Return value optimization - omits copy constructor since return value is a prvalue.
	return Complex(m_Real + rhs.m_Real, m_Imaginary + rhs.m_Imaginary);
}

template <typename R, typename I>
Complex<R, I> Complex<R, I>::operator-(const Complex &rhs) {
	// RVO optimization.
	return Complex(m_Real - rhs.m_Real, m_Imaginary - rhs.m_Imaginary);
}

template <typename R, typename I>
Complex<R, I> Complex<R, I>::operator*(const Complex &rhs) {
	return Complex(m_Real * rhs.m_Real, m_Imaginary * rhs.m_Imaginary);
}

template <typename R, typename I>
Complex<R, I>& Complex<R, I>::operator=(const Complex &rhs) {
	if (this == rhs) {
		return this;
	}
	m_Real = rhs.m_Real;
	m_Imaginary = rhs.m_Imaginary;
	return this;
}

template <typename V, typename W>
std::ostream& operator<<(std::ostream &os, const Complex<V, W> &rhs) {
	os << '(' << rhs.m_Real << ',' << rhs.m_Imaginary << ')';
	return os;
}

template <typename R, typename I>
void Complex<R, I>::ScreenOutput() const {
	std::cout << '(' << m_Real << ',' << m_Imaginary << ')';
}


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
		vec.push_back(cNum);
	}
}

template <typename R, typename I>
void AddVectors(
	std::vector<Complex<R, I>> &vec1,
	const std::vector<Complex<R, I>> &vec2,
	std::vector<Complex<R,I>> &vec3) {
	// Get the size of the vector.
	int vSize = vec1.size();
	// Go through the vectors
	for (int i = 0; i < vSize; i++) {
		// Perform addition of corresponding components and add result to vec3.
		vec3.push_back(vec1[i] + vec2[i]);
	}
}

template <typename R, typename I>
void PrintVector(const std::vector<Complex<R, I>> &vec) {
	int vSize = vec.size();
	std::cout << '[';
	for (int i = 0; i < vSize; i++) {
		std::cout << vec[i];
	}
	std::cout << ']';
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