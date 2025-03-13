#include <iostream>
void foo(int&& r) {
	std::cout << "foo(int&& r)\n";
}
void foo(const int& r) {
	std::cout << "foo(const int& r)\n";
}
void func(int&& r) {
	foo(r);
}

int main(void) {
	func(123);
}