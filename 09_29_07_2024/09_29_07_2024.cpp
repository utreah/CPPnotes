#include <iostream>
#include <vector>

int main() {
	using namespace std;

	vector<int> v{ 1, 4, 7, 12, 8 };
	v.at(2) = 5;
	auto aval = v.at(3);
	// Burada hem vector üzerinde deðiþiklik yapabildik hem de döndürdüðü referansý bir deðiþkende tuttuk.
	
	const vector<int> cv{ 1, 4, 7, 12, 8 };
	auto v1 = cv.at(3); 
	cv.at(4) = 2; // sentaks hatasý veriyor çünkü cv vektorü const. Const overloading yüzünden const int& döndüren sýnýf fonksiyonunu
					// çaðýrýyor. Bundan dolayý deðiþiklik yapýlamýyor vektör üzerinde. 
}