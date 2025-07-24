#include <iostream>
class myClass {
public:
	myClass(){
		std::cout << "myClass default ctor this = " << this << '\n';
		/*myClass ctoru non-static member function olduðu için this pointerýný kullanarak bu sýnýf nesnesini çaðýraný görücez*/
	}
	~myClass() {
		std::cout << "myClass destructor this = " << this << '\n';
	}

};
void func() {
	static int cnt{};
	std::cout << "func " << ++cnt << ". kez cagrildi" << '\n';
	static myClass m4;
}
myClass m1, m2, m3;
int main() {

	std::cout << "main has just started" << '\n';
	func();
	func();
	func();
	func();
	std::cout << "main is finishing" << '\n';
}