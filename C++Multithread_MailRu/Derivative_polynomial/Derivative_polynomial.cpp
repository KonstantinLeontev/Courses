#include <iostream>
#include <set>
#include <regex>
#include <string>

struct Member {
	Member () : coef(1), power(1) {}
	Member (int c, int p) : coef(c), power(p) {}

	bool operator<(const Member &rh) const { return power < rh.power; }

	mutable int coef;
	int power;
};

bool input (std::string &in){
	std::cout << "\nEnter a polynome or '0' to quit: ";
	std::cin >> in;
	if (in == "0"){
		std::cout << "Goodbye!\n"; 
		return false;
	}
	else return true;
}

void derivative(Member &m) {
         m.coef *= m.power;
         m.power--;
}

void convert(std::string &in, std::set<Member> &members){
	// Parse the string to coefficient and powers for each member.
	// Regex pattern for 1 member in pseudo code is (sign)(coeff)*(x)^(power).
	std::regex reg ("([\\+-]?\\d*)?\\*?x\\^?(\\d*)?");
	std::sregex_iterator iter(in.cbegin(), in.cend(), reg);
	const std::sregex_iterator end; // Implicitly initilized to the end value.
 	std::string temp{};

	for ( ; iter != end; ++iter) {
		Member m;

		// Get a coefficient.
		temp = (*iter)[1].str();
                if (temp != ""){
			if (temp == "-") {
				m.coef = -1;
			}
			else if (temp != "+") {
                        	m.coef = std::stoi(temp);
			}
                }

		// Get a power.
		temp = (*iter)[2].str();
		if (temp != ""){
			m.power = std::stoi(temp);
		}
		
		derivative(m);
		
		// Check for the member that is already in the set and have the same power.
		std::set<Member>::iterator i = members.find(m);
		if (i != std::end(members)) {
			// Increase the coefficient for that member.
			i->coef += m.coef;
		}
		else {
			members.insert(m);
		}
	}
}

void output(std::set<Member> &members) {
	std::reverse_iterator<std::set<Member>::iterator> iter = members.rbegin();

	for (; iter != members.rend(); ++iter){
		if (iter->coef) {
			if ( iter->coef > 0) {
				if (iter != members.rbegin()) {
					std::cout << '+';
				}
				std::cout << iter->coef;
			}
			else if (iter->coef < -1) {
				std::cout << iter->coef;
			}
			else if (iter->coef == -1) {
				std::cout << '-';
				if (!iter->power) {
					std::cout << 1;
				}
			}
			if (iter->power) {
				if (iter->coef != -1) {
					std::cout << '*';
				}
				std::cout << 'x';
				if (iter->power > 1) {
					std::cout << '^' << iter->power;
				}
			}
		}
	}
}

// Version for Stepik test.
std::string sderivative(std::string polynomial){
	std::string result{};
	std::map<int, int> m; // Power and coefficient.

	std::regex reg ("([\\+-]?\\d*)?\\*?x\\^?(\\d*)?");
	std::sregex_iterator iter(polynomial.cbegin(), polynomial.cend(), reg);
	const std::sregex_iterator end;

	// Build a map for all members of polynomial.
	for (; iter != end; ++iter) {
		int power{1}, coef{1};

		// Get a coefficient.
		result = (*iter)[1].str();
		if (result != "" && result != "+") {
			if (result != "-") {
				coef = std::stoi(result);
			}
			else {
				coef = -1;
			}
		}

		// Get a power.
		result = (*iter)[2].str();
		if (result != "") {
			power = std::stoi(result);
		}

		// Calculate the derivative value.
		coef *= power;
		power--;

		// Check if another member with this power value already exists.
		std::map<int, int>::iterator i = m.find(power);
		if (i != std::end(m)) {
			i->second += coef;
		}
		else {
			m.insert(std::map<int, int>::value_type(power, coef));
		} 
	}

	// Build a string with derivative of polynome.
	result = "";
	std::reverse_iterator<std::map<int, int>::iterator> riter = m.rbegin();
	for (; riter != m.rend(); ++riter) {
		if (riter->second) {
			// Coefficient part.
			if (riter->second != -1) {
				if (riter != m.rbegin() && riter->second > 0) {
					result += "+";
				}
				result += std::to_string(riter->second);
			}
			else {
				result += "-";
				if (!riter->first) {
					result += "1";
				}
			}
			// Power part.
			if (riter->first) {
				if (riter->second != -1) {
					result += "*";
				}
				result += "x";
				if (riter->first > 1) {
					result += "^" + std::to_string(riter->first);
				}
			}
		}		
	}
return result;
}

int main (){
	std::string in{};
	
	while (input(in)){
		std::set<Member> members{}; 

		convert(in, members);
		output(members);

		in = sderivative(in);
		std::cout << "\nString output: " << in;
	} 
}
