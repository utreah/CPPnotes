#include <vector>
#include <iostream>
int main(void) {
	using namespace std;

	vector<int> ivec{ 4, 5, 3, 2, 6, 8, 0, };
	auto iter = ivec.begin();
	
	vector<int>::iterator iter2 = ivec.begin();
	cout << *iter;
	++*iter;
	*iter = 987;
}