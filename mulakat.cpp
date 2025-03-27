//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Dilde bir aracý öðrenirken þu sorularý sor
1) Ne iþe yarýyor?
2) Compile time / run time nerede çalýþýyor (mülakatlarda sorabiliyorlar bunu)
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
03_08_07_2024
MÜLAKATLARDA HOCA BU SORUYU ÇOK SORUYORMUÞ
	SORU: Aþaðýdaki kod çalýþtýrýldýðýnda ekrana yazdýrýlacak x'in deðeri ne olur?
*/
// c kodu;
int main(){
	int x = 5;
	foo(x); // foo bir fonksiyon
	printf("%d", x);
}
/*
	CEVAP: Burada x nesnesi foo fonksiyonuna call by value ile gönderildiði için
		foo içerisinde nasýl bir iþlem yapýlýrsa yapýlsýn x'in deðeri 5 olacak ve ekrana 5 yazdýrýlacak.
			Eðer "foo'nun kodunu görmek gerek" derseniz 3152 kapýdan dýþarý.
	Bu durum C için geçerli CPP için ise cevap "foo kodunu görmem gerek" Bunun sebebi
		fonksiyon l value referans semantiði olarak kodlandý ise x'in deðeri deðiþir, eðer call by value ise
			deðiþmez.
*/

int foo(int a){
	a = 4;
} // eðer foo böyle tanýmlandý ise bu call bu value, x deðeri deðiþmez.

int foo(int& a){
	a = 4;
}// foo fonksiyonu l value referans semantiði ile tanýmlanmýþ x'in deðeri deðiþir.
Özetle: 
	C kodu için: Call by value olduðu için deðer deðiþmez.
	CPP kodu için: Fonksiyonun tanýmý gerekli. 
/------------------------------------------------------------------------------------------------------------------------/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
04_10_07_2024
MÜLAKATTA ÇIKMA ÝHTÝMALÝ YÜKSEK BUNUN!
*/
int y = 10;
decltype(y); // L value yani int&
decltype((y)); // L value çünkü parantez içine alýnca ifade olarak ele alýnmasýný söylemiþ olduk yani L value oluyor 
				// ve o da int&
-------------------------------------------------
/*
HATIRLATMA!
Maximal Munch:Derleyici tokenizing yaparken en uzun tokený elde etmeye çalýþýyor.
	whitespace karakterine kadar olan tokenlarý ayýra ayýra gidiyor. Yani

	void foo(const char *= nullptr) burada *= ayrý bir operatör olarak iþlenir çünkü const chardan sonra
		whitespace olduðu için const char olarak ele alýnýr.
	void foo(const char* = nullptr) burada ise const char* default argument olarak nullptr alýyor.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
07_22_07_2024.cpp
MÜLAKAT SORUSU!!!
func(123) yani R value ile çaðrýlýyor.Ekrana çýktý yapacak fonksiyon hangisi olur ?
*/

#include <iostream>
void foo(int&& r) {
	std::cout << "foo(int&& r)\n";
}
void foo(const int& r) {
	std::cout << "foo(const int& r)\n";
}
void func(int&& r) {
	foo(r);
}

int main(void) {
	func(123);
}
/*
CEVAP:
Ekrana const int& r parametreli fonksiyon yazar.func R value reference ile çaðrýlýyor.
foo ise r nesnesi ile yani L value reference ile çaðrýlýyor. const int& hem L hem R value ref alýyor.
Burada foo'nun gönderdiði nesnenin Veri türü int&&. Referans kategorisi ile veri türü karýþtýrýlmamalý.
r'nin int&& olmasý onun referans kategorisi ile alakasý yok. Bir nesnenin ismi her zaman L value reftir.

int x; -> x'in deðer kategorisi yoktur. Deðer kategorileri ifadeler için vardýr.
int &r; -> Bu deðiþkenin data type'ý int&
	r-> fakat bu ifadenin primary value categorysinin ne olduðu baþka bir þey.
int &&rf; -> Data type'ý int&& fakat value kategorisi ifadenin kullanýldýðý yere göre deðiþir. 
	Ortada bir isim var ise, ismin oluþturduuðu ifade L value expressiondur. 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 09_29_07_2024 ve 08_24_07_2024
class myclass {
public:
	void bar(double x);
private:
	void bar(int x);
};
int main() {
	myclass m;
	m.bar(12);
	/*
		Bu sentaks hatasý! Sebebi ise name lookup sürecinde double parametreli fonksiyonda int türünden
			double türüne promotion var ama private bölümde olan int parametreli fonksiyon ile exact match var.
			Bundan dolayý name lookup int parametreli fonksiyonda sonlanacak, context kontrolü yapýlacak ve SON olarak
			access control yapýldýðýnda sentaks hatasý verecek. Çünkü int parametreli fonksiyon private region içerisinde
			ve client kod bu bölüme eriþemez. Bundan dolayý access control safhasýnda sentaks hatasý verecek.
	*/
	m.bar(1.2); // bu sentaks hatasý deðil access control kýsmý baþarýlý olacak ve çalýþacak.
	/*
		// bu fonksiyonu globalde tanýmladýðýný düþün
		void myclass::bar(int x){
			bar(x); // bu sefer int parametreli çaðrýlacak
		}
	*/
}