#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
void print_date(int day = -1, int month = -1, int year = -1);
int main(void) {
	print_date(4, 6, 1987);
	print_date(4, 6);
	print_date(4);
	print_date();
}

void print_date(int d, int m, int y) {
	std::time_t sec;
	std::time(&sec);
	std::tm* p = std::localtime(&sec);
	if (y == -1) {
		y = p->tm_year + 1900;
		if (m == -1) {
			m = p->tm_mon + 1;
			if (d == -1)
				d = p->tm_mday;
		}
	}
	std::cout << d << '/' << m << '/' << y << std::endl;
}