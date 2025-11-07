#include <iostream>
#include "main.h"


int main() {
	Mint m1{ 367 }, m2{ 988 }, m3{ 512 }, m4;
	m4 = m1 * m2 + m3;
	
	std::cout << "uc tam sayi giriniz: ";
	std::cin >> m1 >> m2 >> m3;
	std::cout << m1 << "" << m2 << "" << m3 << "Total: " << m1 +  m2 + m3 << "\n";
}