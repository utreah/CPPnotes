#include <iostream>
class Myclass {
public:
	explicit Myclass(int) { std::cout << "Int parametre\n"; }
	Myclass(double) { std::cout << "Double parametre\n"; }
};
int main()
{
	Myclass m = 12;
}