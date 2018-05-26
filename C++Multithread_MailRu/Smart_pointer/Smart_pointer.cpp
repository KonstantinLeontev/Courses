#include <iostream>

class StringPointer {
public:
	std::string *operator->() {
		if (!mPointer) mPointer = new std::string("");
		return mPointer;
	}
	operator std::string*() {
		if (!mPointer)	mPointer = new std::string("");
		return mPointer;
	}
	StringPointer(std::string *Pointer) : mPointer(Pointer) {}
	~StringPointer(){ if (*mPointer == "") delete mPointer;}

private:
	std::string *mPointer;
};

int main (int argc, char **argv){
	std::string s1 = "Hello, world!";

	StringPointer sp1(&s1);
	StringPointer sp2(NULL);

	std::cout << sp1->length() << std::endl;
	std::cout << *sp1 << std::endl;
	std::cout << sp2->length() << std::endl;
	std::cout << *sp2 << std::endl;
}
