#include <iostream>
int foo(int x = 10, int y = 20, int z = 30);
int main(void) {
	int x{};
	int& r1 = get_value();
	std::cout << "r1 value = " << r1 << '\n';
}
19:27