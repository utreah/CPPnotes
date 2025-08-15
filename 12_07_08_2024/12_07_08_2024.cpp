#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class String {
public:
	

	String& operator=(const String& other)
	{
		if (this == &other) // eðer bu true dönerse self-assignemnt var demek.
			return *this;
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
	String(String&& other) : mlen(other.mlen), mp(other.mp)  // copy constructor
	{ 
		/*
			Hayata sona erecek nesnenin pointerý ve string uzunluðu kopyalandý. String sýnýfýnýn destructorý
				eðer mp nullptr tutmuyor ise free ediyor. Bundan dolayý bizde mp'yi nullptr yapýyoruz. Bu sayede ömrü sona eren
					nesnenin destructorý çaðýrýlsa bile mp free edilmiyor. 
		*/
		other.mp = nullptr;
		other.mlen = 0; // bunu neden 0 yaptýðýmýzý hoca ileride anlatýcam dedi
	}
	String& operator=(String&& other)
	{
		if (this == &other)
			return *this;
		std::free(mp); // bunu yapmamýzýn sebebi kaynak sýzýntýsý önlemek
		mlen = other.mlen;
		mp = other.mp;

		other.mp = nullptr;
		other.mlen = 0;
		return *this;
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
	String str(String{ "Bugun hava cok guzel" });
	str.print();
}