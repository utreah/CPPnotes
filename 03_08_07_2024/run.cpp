#include <iostream>
int main()
{
	int x = 10, y = 20, z = 30;
	int* p[3] = { &x, &y, &z };

	int& r[3] = { &x, &y, &z };
}