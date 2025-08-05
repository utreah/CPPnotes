#include <iostream>
#include <cstdlib>
class String {
public:
	String(const char*);
	~String()
	{
		if (mp)
			std::free(mp);
	}
private:
	char* mp; // yazýnýn adresinin tutulduðu handle
	std::size_t mlen; // yazýnýn boyutunun tutulduðu data member
};

int main() {
	String str("bugun sinifin ozel fonksiyonlarini isliyoruz");

	String str2 = str;
}