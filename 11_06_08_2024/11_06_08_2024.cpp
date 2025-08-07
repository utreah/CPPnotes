#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
class String {
public:
	String& operator=(const String& other) 
	{
		mlen = other.length();
		std::free(mp);
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << ("cannot allocate memory\n");
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, other.mp); 
		return *this;
	}
	String(const String& other) : mlen(other.mlen) // eðer burada mlen'i MIL ile hayata getirmeseydik derleyici otomatik olarak default initialization yapacaktý
	{
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << ("cannot allocate memory\n");
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, other.mp); // other.mp kopyalama iþlemi yaptýðýmýz sýnýf nesnesinden deðiþkenin referansýný kullanarak adreste tutulan yazýyý
		// yeni adrese kopyalýyoruz.
	}
	String(const char* p) : mlen(std::strlen(p))
	{
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << ("cannot allocate memory\n");
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}
	~String()
	{
		if (mp)
			std::free(mp);
	}
	std::size_t length()const
	{
		return mlen;
	}
	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}
private:
	std::size_t mlen;
	char* mp;
};
  
int main() {
	String str("bugun sinifin ozel fonksiyonlarini isliyoruz");

	str.print();
	if (str.length() > 10) {
		String sx("Ben blok icerisinde kullanilacak bir yaziyim");
		sx.print();
		sx = str;
		sx.print();
		(void)getchar();
	}
	str.print();
}