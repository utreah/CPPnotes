#include <iostream>

void foo(int* param) {
	std::cout << "Value of param: " << *param << std::endl;
}
void foo(const int* param) {
	std::cout << "Value of param: " << *param << std::endl;
}

int main(void) {
	const int x{ 45 };
	int y{ 66 };

	foo(&x); // x const nesne ve const T* türünden T* türüne örtülü dönüþüm yok.
	// bundan dolayý foo(int*) fonksiyonu viable bile deðil. const int* parametreli fonksiyon çaðrýlacak.
	foo(&y); // burada her iki fonksiyonda viable olacak. Derleyici const olmayan parametreli fonksiyona
	// öncelik tanýdýðý için int* parametreli fonksiyon çaðrýlacak
}
