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
	std::cout << "Enter a polynome or '0' to quit: ";
	std::cin >> in;
	if (in == "0"){
		std::cout << "Goodbye!\n"; 
		return false;
	}
	else return true;
}

void convert(std::string &in, std::set<Member> &members){
	// Parse the string to coefficient and powers for each member.
	// Regex pattern for 1 member in pseudo code is (sign)(coeff)*(x)^(power).
	std::regex reg ("(\\+|-)?(\\d*)?\\*?x\\^?(\\d*)?");
	std::sregex_iterator iter(in.cbegin(), in.cend(), reg);
	const std::sregex_iterator end; // Implicitly initilized to the end value.
 
	for (iter; iter != end; ++iter) {
		Member m{};

		m.sign = std::stoi((*iter)[0]);
		m.coef = std::stoi((*iter)[1]);
		m.power = std::stoi((*iter)[2]);
		
		members.insert(m);
	}
}

void output(std::set<Member> &members) {
	std::set<Member>::iterator iter = members.begin();
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
		std::set<Member> members{}; 

		convert(in, members);
		output(members); 
	} 
}
