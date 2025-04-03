#include <iostream>
class Myclass {
public:
	void func();
};
void Myclass::func() {
	std::cout << "this = " << this << '\n';
}
int main() {
	Myclass m;
	std::cout << "&m = " << &m << '\n';
	m.func();
}