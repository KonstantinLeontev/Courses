#include <iostream>
#include <set>
#include <regex>
#include <string>

struct Member {
	Member () : sign('+'), coef(1), power(1) {}
	Member (char s, int c, int p) : sign(s), coef(c), power(p) {}

	bool operator<(const Member &rh) const { return power < rh.power; }

	char sign;
	int coef;
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

void convert(std::string &in, std::multiset<Member> &members){
	// Parse the string to coefficient and powers for each member.
	// Regex pattern for 1 member in pseudo code is (sign)(coeff)*(x)^(power).
	std::regex reg ("(\\+|-)?(\\d*)?\\*?x\\^?(\\d*)?");
	std::sregex_iterator iter(in.cbegin(), in.cend(), reg);
	const std::sregex_iterator end; // Implicitly initilized to the end value.
 	std::string temp{};

	for ( ; iter != end; ++iter) {
		Member m;
		
		temp = (*iter)[1].str();
		if (temp != ""){
			m.sign = temp[0];
		}

		temp = (*iter)[2].str();
                if (temp != ""){
                        m.coef = std::stoi(temp);
                }

		temp = (*iter)[3].str();
		if (temp != ""){
			m.power = std::stoi(temp);
		}
	
		members.insert(m);
	}
}

void output(std::multiset<Member> &members) {
	std::set<Member>::iterator iter = members.begin();

	// Output only '-' sign for the first element.
	if ((*iter).sign == '-') {
		std::cout << '-';
	}
	if ((*iter).coef > 1) {
		std::cout << (*iter).coef << '*';
	}
	std::cout << 'x';
	if ((*iter).power > 1) {
		std::cout << (*iter).power;
	}
	++iter;

	for (; iter != members.end(); ++iter){
		std::cout << (*iter).sign;
		if ((*iter).coef > 1) std::cout << (*iter).coef << '*';
		std::cout << 'x';
		if ((*iter).power > 1) std::cout << '^' << (*iter).power;
	}
}

int main (){
	std::string in{};
	
	while (input(in)){
		std::multiset<Member> members{}; 

		convert(in, members);
		output(members); 
	} 
}
