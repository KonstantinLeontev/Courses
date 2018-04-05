#include <iostream>
#include <vector>
#include <limits> // For checking max templated values - numeric_limits.
#include <string>

template <typename R, typename I>
class Complex {
public:
	Complex() : m_Real{}, m_Imaginary{} {} // Value initialization (since C++ 11).
	Complex(R real, I imaginary) : m_Real(real), m_Imaginary(imaginary){} // With arguments.
	Complex(const Complex &rhs) : m_Real(rhs.m_Real), m_Imaginary(rhs.m_Imaginary) {}
	~Complex() {}

	void SetReal(const R &real) { m_Real = real; }
	void SetImaginary(const I &imaginary) { m_Imaginary = imaginary; }
	R GetReal() const { return m_Real; }
	I GetImaginary() const { return m_Imaginary; }

	void Add(const Complex &rhs);
	void Subtract(const Complex &rhs);
	void Product(const Complex &rhs);
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

	// Limits to check limit size of template types.
	static const R m_Rmin = std::numeric_limits<R>::min();
	static const R m_Rmax = std::numeric_limits<R>::max();
	static const I m_Imin = std::numeric_limits<I>::min();
	static const I m_Imax = std::numeric_limits<I>::max();
	// Methods for checking type overflow in try blocks.
	int CheckLimitsAdd(const Complex &rhs) const;
	int CheckLimitsSub(const Complex &rhs) const;
	int CheckLimitsProd(const Complex &rhs) const;
	// Display error message in a catch block.
	void ErrorOverflowMsg(const std::string operation, const Complex &rhs, int &check) const;
};

template <typename R, typename I>
void Complex<R, I>::ErrorOverflowMsg(const std::string operation, const Complex &rhs, int &check) const {
	std::cout << "Overflow error. Cannot perform an " << operation << " in ";
	// Output if error was in the real part of the number.
	if (check == 1) {
		std::cout << "real part of the number:\n"
			<< "m_Real = " << m_Real << ", rhs.m_Real = " << rhs.m_Real << '\n'	
			<< "R max value = " << m_Rmax << ", R min value = " << m_Rmin << '\n';
	}
	// Output if error was in the imaginary part of the number.
	else {
		std::cout << "imaginary part of the number:\n"
			<< "m_Imaginary = " << m_Imaginary << ", rhs.m_Imaginary = " << rhs.m_Imaginary
			<< "I max value = " << m_Imax << ", I min value = " << m_Imin << '\n';
	}	
}

template <typename R, typename I>
void Complex<R, I>::Add(const Complex &rhs) {
	try {
		int check = CheckLimitsAdd(rhs);
		// Check for type overflow.
		if (check) {
			throw check;
		}
		// If no exception trown then perform addition.
		m_Real += rhs.GetReal();
		m_Imaginary += rhs.GetImaginary();
	}
	catch (int check) {
		ErrorOverflowMsg("addition", rhs, check);
	}
}

template <typename R, typename I>
void Complex<R, I>::Subtract(const Complex &rhs){
	try {
		// Check for type overflow.
		int check = CheckLimitsSub(rhs);
		if (check) {
			throw check;
		}
		// If no exception thrown then perform subtraction.
		m_Real -= rhs.GetReal();
		m_Imaginary -= rhs.GetImaginary();
	}
	catch (int check) {
		// Show appropriate error message.
		ErrorOverflowMsg("subtraction", rhs, check);
	}
}

template <typename R, typename I>
void Complex<R, I>::Product(const Complex &rhs) {
	try {
		// Check for type overflow.
		int check = CheckLimitsProd(rhs);
		if (check) {
			throw check;
		}
		// Perform product if there are no errors here.
		m_Real *= rhs.GetReal();
		m_Imaginary *= rhs.GetImaginary();
	}
	catch (int check) {
		// Show error message.
		ErrorOverflowMsg("product", rhs, check);
	}
}

template <typename R, typename I>
int Complex<R, I>::CheckLimitsAdd(const Complex &rhs) const {
	// Check the real part.
	if (rhs.GetReal() > 0 && (m_Rmax - rhs.GetReal()) < m_Real) return 1;
	if (rhs.GetReal() < 0 && (m_Rmin + rhs.GetReal()) > m_Real) return 1;
	// Check the imaginary part
	if (rhs.GetImaginary() > 0 && (m_Imax - rhs.GetImaginary()) < m_Real) return 2;
	if (rhs.GetImaginary() < 0 && (m_Imin + rhs.GetImaginary()) > m_Imaginary) return 2;
	// If everything is OK.
	return 0;
}

template <typename R, typename I>
int Complex<R, I>::CheckLimitsSub(const Complex &rhs) const {
	// Check the real part.
	if (rhs.GetReal() > 0 && (m_Rmin + rhs.GetReal()) > m_Real) return 1;
	if (rhs.GetReal() < 0 && (m_Rmin - rhs.GetReal()) > m_Real) return 1;
	// Check the imaginary part.
	if (rhs.GetImaginary() > 0 && (m_Imin + rhs.GetImaginary()) > m_Imaginary) return 2;
	if (rhs.GetImaginary() < 0 && (m_Imin - rhs.GetImaginary()) > m_Imaginary) return 2;
	// Return 0 if there are no any errors.
	return 0;
}

template <typename R, typename I>
int Complex<R, I>::CheckLimitsProd(const Complex &rhs) const {
	// Check the real part.
	if (rhs.GetReal() > 0) {
		if (m_Real > 0 && (m_Rmax / rhs.GetReal()) < m_Real) return 1;
		if (m_Real < 0 && (m_Rmin / rhs.GetReal()) > m_Real) return 1;
	}	
	// Check the imaginary part.
	if (rhs.GetImaginary() > 0) {
		if (m_Imaginary > 0 && (m_Imax / rhs.GetImaginary()) < m_Imaginary) return 2;
		if (m_Imaginary < 0 && (m_Imin / rhs.GetImaginary()) > m_Imaginary) return 2;
	}
	// Return 0 if there are no any errors.
	return 0;
}

template <typename R, typename I>
Complex<R, I> Complex<R, I>::operator+(const Complex &rhs) {
	try {
		int check = CheckLimitsAdd(rhs);
		if (check) {
			throw check;
		}
		// Return value optimization - omits copy constructor since return value is a prvalue.
		return Complex(m_Real + rhs.m_Real, m_Imaginary + rhs.m_Imaginary);
	}
	catch (int check) {
		// Show error message and return this object.
		ErrorOverflowMsg("addition", rhs, check);
		return *this;
	}
}

template <typename R, typename I>
Complex<R, I> Complex<R, I>::operator-(const Complex &rhs) {
	try {
		// Check for type overflow.
		int check = CheckLimitsSub(rhs);
		if (check) {
			throw check;
		}
		// RVO optimization.
		return Complex(m_Real - rhs.m_Real, m_Imaginary - rhs.m_Imaginary);
	}
	catch (int check) {
		// Show error message and return this object.
		ErrorOverflowMsg("subtraction", rhs, check);
		return *this;
	}
}

template <typename R, typename I>
Complex<R, I> Complex<R, I>::operator*(const Complex &rhs) {
	try {
		// Check for type overflow.
		int check = CheckLimitsProd(rhs);
		if (check) {
			throw check;
		}
		// If everything is OK then perform product and return result object.
		return Complex(m_Real * rhs.m_Real, m_Imaginary * rhs.m_Imaginary);
	}
	catch (int check) {
		// Show error message and return this object.
		ErrorOverflowMsg("product", rhs, check);
		return *this;
	}
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
		if (i != vSize - 1) {
			std::cout << ',';
		}
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