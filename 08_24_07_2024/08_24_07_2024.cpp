#include <iostream>
int y;
class mystruct{
	int x, y;
	 
};
int main() {
	mystruct nec;
	std::cout << "sizeof(nec) = " << sizeof(nec) << std::endl;
}