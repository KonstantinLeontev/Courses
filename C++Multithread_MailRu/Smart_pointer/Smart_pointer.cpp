#include <iostream>

template<typename Type>
class SmartPointer {
private:
	Type* pointer;

public:
	SmartPointer(Type* p) : pointer(p){}
	operator Type*(){return pointer;}
	Type *operator->(){
		if (pointer) {
			return pointer;
		}
		else {
			std::cerr << "Bad pointer!" << std::endl;
			return new Type;
		}
	}
	std::ptrdiff_t operator-(SmartPointer<Type> p) {
		return pointer - p;
	}

	std::ptrdiff_t operator-(void *p) {
		return pointer - p;
	}
};        

class Foo {
private:
	int a, b;

public:
	Foo() : a(0), b(0){}
	Foo(int a, int b) : a(a), b(b){}
	int Sum(){return a + b;}
};

int main (int argc, char **argv){
	SmartPointer<Foo> sp(NULL);
	std::cout << sp->Sum() << std::endl;
}
