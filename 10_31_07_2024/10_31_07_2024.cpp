#include <iostream>
#include <string>
class Map {
	// Derleyici tarafýndan implicitly-declared bir fonksiyon bildirilecek fakat bu fonksiyon sentaks hatasýna sebep olacka.
		// çünkü int& bir l value reference ve sadece l value deðer alabilir. Default init edildiðinde garbage value verilecek
			// yani verilen deðer r value olduðu için sentaks hatasý oluþacak ve bu yazýlan default constructor delete edilecek.
private:
	int& mx;
};
int main(){}