#include <iostream>
/*
Referans kategoriler
- L value reference
- R value reference
- Universal / forwarding reference
*/

/////////////////////////////////////////////////////

// DEFAULT ARGUMENT

// int foo(int, int, int); // bu normal bir fonksiyon deklarasyonu
void foo(int a = 30, int b = 20, int c = 10) // bu ise 3. parametresi default olan bir fonksiyon.
{								// default parametreye sahip olmas� demek 3. parametrenin sadece 10 de�erini almas� demek de�il.
									// 3. parametreye e�er bir de�er g�nderilmez ise 10 de�erini alacak demek. default argument asl�nda bu anlama geliyor.
								// default argument program�n derleme zaman�nda kullan�lan/belli olan bir ara�
	std::cout << "a = " << a << "  b = " << b << "  c = " << c << std::endl;
}
int main(void) {
	foo(31, 52, 69); // ekrana 31, 52, 69 yazd�r�r
	foo(31, 52);	// ekrana 31 52 10 yazd�r�r
	foo(31);		// ekrana 31 20 10 yazd�r�r
	foo();			// ekrana 30 20 10 yazd�r�r
}
// referans ve pointelar da default argument olabilirler.
int x = 10;
int fooptr(int* p = nullptr, int* p2 = &x);
int fooref(int& b = x);
// default arg�man�n constant bir ifade olma zorunlulu�u yoktur. 
int bar(int x = fooptr()); // legal, default de�er ba�ka bir fonksiyonun d�n�� de�eri olabilir.


void func(int *= &x); // burada derleyici hata veriyor, bunun sebebi maximal munch kural�.
	// parametre tokenlar�na ayr�ld���nda  parametreyi int* t�r� olarak de�il int t�r�nden bir ifadeye
		// atama i�lemi yap�yor (de�eri adres g ile �arp�yor)

void func2(int* a = &x); // isim verdi�imizde bu durum ortadan kalk�yor tabii.
	// fonksiyon parametrelerini isimlendirmesek bile kabul oluyor. C'de g�rd�k bunu


void foobar(int x = ++x);

int main(void) {
	foo(); // ekrana 6 yazar
	foo(); // ekrana 7 yazar
	foo(); // ekrana 8 yazar
}

void foobar(int a) {

	std::cout << a;
}

int func3() {
	static int x = 0;

	return ++x;
}

void baz(int x = func3()) {
	std::cout << x;
}

int main() {
	baz(func3()); // ekrana 1 yazd�r�r 
	baz(func3()); // ekrana 2 yazd�r�r
	baz(func3()); // ekrana 3 yazd�r�r
}
//////////////////////////////////////////
void funct(int x, int y = x); // bu ge�erli de�il, bir parametrenin default de�eri kendisinden �nceki parametre olamaz.


int print_date(int day = -1, int month = -1, int year = -1) // Baz� fonksiyonlarda default de�erin kullan�l�p kullan�lmad���n�
// anlamak i�in default de�er kullan�l�yor. Tabii bu kullan�lmayan de�erin
// nas�l yorumlanaca�� d�k�mantasyonda belirtilmek zorunda.
// mesela bu fonksiyon i�in e�er arg�man alm�yor ise, g�ncel tarihi kullan�yor olabilir. 
// implementasyona ba�l�. D�k�mantasyonda belirtilir.

///////////////////////////////////////////////////////////////////////////
/*                                                     auto type deduction                                                       */

int x = 10;
auto int x = 10; // bu iki ifade C dilinde ayn�, auto burada x'in otomatik �m�rl� oldu�unu belirtiyor. Modern CPP'de sentaks hatas�


// Modern CPP'de place holder olarak g�rev yap�yor. Derleme zaman�nda belli olur.
// Type deduction auto keyword� kar��l���nda yap�l�r. auto bir type holder olarak g�rev yapar ve derleyici auto yerine gelecek
	// t�r� anlar.
// auto'nun t�r� anla��ld���nda de�i�keninde t�r� anla��labilir.
	// auto'ya kar��l�k gelen t�r ile de�i�kenin t�r� ayn� olmak zorunda de�il.
// auto ile default init yap�lamaz. Copy ya da direct init olmak zorunda
// Bu iki �eyi bilmiyorsan kapat pcyi git ��renme cpp
	//- �fadenin t�r�
	// - �fadenin de�er kategorisi

	// Value category ifadeyi niteler.
int x = 10; // x'in de�er kategorisi ne? e�er L value - R value diyorsan YANLI�!
// bir de�i�kenin value categorysi olmaz. x'in sadece data type'� olur.

/* E�er ��yle yazarsak;
	x; ahanda �imdi value categorysi var ve l value
	+x; PR value
	Uzun laf�n k�sas�, e�er bir de�i�ken tan�ml�yorsak onun kategorisi de�il veri t�r� var.
	int x = 10; -> veri t�r� var(int), de�er kategorisi yok.
	x; -> de�er kategorisi var
	int* y = nullptr; veri t�r� var(int*)
	int& r = x; // de�er t�r� int& (intref)
	y; -> veri t�r� int*
	x -> veri t�r� int
	peki ya r; ifadesinin veri t�r� ne? int& diyorsan enseye �apla�� yedin
	r; -> bunun veri t�r� int. ��nk� bir ifadenin t�r� ref(&) t�r�nden olamaz.

*/



int main() {
	auto x = 10; // auto'n�n kullan�labilmesi i�in ya direct ya da copy olarak init edilmesi ZORUNLU!
	// auto x(10); direct init, �stteki de copy init.	
	// auto'ya kar��l�k gelen de�er, initializer expressiondan anla��lacak. 
//////////////////////////////////////////////
// E�er ilk de�er veren ifade const bir ifade ise constluk d��er.

const int xyz = 10;
auto autox = xyz; // bunun veri t�r� const int de�il sadece int

int x1 = 10;
int xref = x1;

auto kz = xref; // bu int& de�il sadece int
kz = 999; // yap�ld���nda sadece kz'nin de�eri de�i�ir, intref olsayd� x1'de de�i�irdi.

int ar[5]{};
auto autoarr = ar; // ar burada array decaye u�rar. Bundan dolay� autoarr'nin veri t�r� int* t�r�nden olur
const int ar[5]{}; // b�yle oldu�unda ise autoarr, const int* t�r�ne d�n��ecek. 
//////////////////////////////
auto p = "Kadeh"; // Kadek string literali oldu�u i�in -> const char[6];
					// ve burada array decay olaca�� i�inde p'nin veri t�r� -> const char* 
}

int foo(int);
int main(void) {
	auto x = foo; 
	// auto x = &foo; -> function to pointer conversion uyguland�, ondan sonra t�r ��kar�m� yap�l�yor.
	// x'in t�r� int (*)(int) t�r�nden olacak. Fonksiyon i�aret�isi
	// int (*x)(int)
}

// AUTO &IDF = EXPR; -> REFERANS var ise ne olur?

/*
- Her zaman lvalue expression olmak zorunda.
- const d��m�yor
- array decayde uygulanm�yor
int foo(int); -> foo'nun t�r� int(int)
	// e�er function to pointer conversion olur ise int (*)(int) olur.
int main(void){
	int x = 6;
	auto &r = x; -> bu int& r = x; 
	// auto &r2 = 10; -> sentaks hatas�, rvalue ile init edemeyiz.
	////////////////
	const int x2 = 10;
	auto &r2 = x2; -> const int& r2;
	int arr[5] = {1, 2, 3, 4, 5};
	auto &x = arr; -> array decay uygulanmad��� i�in int[dizinin_boyutu] veri t�r�n� al�r.
	// dizi const olursa da "const int (&x)" olurdu.
	
		auto a = "Oguz"; // bu const int* veri t�r�n� alacak
	auto& a2 = "Oguz"; // bu ise const char[5] veri t�r�n� alacak. ��nk� auto&'te array decay olmuyor.

	auto fx = foo; // b�yle yaz�l�ras function decayden dolay� fx'in t�r�
					// int (*fx)(int) olur. 
	auto& fx = foo; // ref olunca decay olmuyordu, bundan dolay� int(&r)(int) olacak fx'in veri t�r�.
						// function reference oldu �
}
*/

///////////////////////////
// auto&&

double bar();

int main(void) {
	int x = 10;
	auto&& r = x; // forwarding/universal reference 
	// Her t�rle veya herhangi bir de�er kategorisi ile ilk de�er verilebilir.
	r = x; // l-value al�r
	r = x + 5; // r-value de al�r
	// E�er ilk de�er veren ifade l-value expression ise
		// autoya kar��l�k gelen ��kar�m int&& olacak. �NEML�!! Bu kar��l�k r de�il auto i�in;
			// int& &&r; veri t�r� haline gelecek.
			
	// E�er ilk de�er veren ifade r-value expression ise
		// autoya kar��l�k gelen ��kar�m int olacak. �NEML�!! Bu kar��l�k r de�il auto i�in;
			// int &&r; veri t�r� haline gelecek. (r value reference)
			
	// yukar�daki iki �rnekte reference to reference oluyor. Normalde reference to reference diye bir �ey yok fakat
		// burada �zel bir kural uygulan�yor. Bu kurala da 'reference collapsin' deniyor.

	// L value auto ===> T&
	// R value auto ===> T

	reference collapsing
	// & -> sol referans, && - sa� referans
		// Bu tabloda referansa bakarken first init. yap�lan ifadenin de�er kategorisini de ele almak zorundas�n.
			// E�er senin sol taraf�n referans� L value ise, first init. de�erin R ise bu sentaks hatas� olur.
				// t�r e� isimi bildirimleri k�sm�nad �rnek var. intrefref &r2 olan �rnek
	REFERANS	REFERANS	SONUC REFERANS
	--------------------------------------
	&				&&			&
	&				&			&
	&&				&			&
	&&				&&			&&
		// T -> t�r/type anlam�nda.
// Yukar�s� biraz kar���k oldu. && (universal referencing) her iki de�er kategorisini b�nyesine alabiliyor.
	// Ald��� de�er kategorisine g�re auto'n�n t�r ��kar�m� yap�l�yor. E�er, auto L-value de�er kategorisine ait bir
		// de�er ile first init. edilir ise T& ��kar�m� yap�l�yor. Bu yap�lan ��kar�m auto i�in de�i�kenin kendisi
			// i�in de�il. int& &&r �eklini alan ifade sol ref + sa� ref oldu�u i�in sonu� referanslar� sol ref oluyor.
				// reference collapsing dedi�imiz bu. Herhangi ��kar�mdan birisinin sol ref olmas�, sonucu sol ref yapar. OR gate gibi
}
////////////////////////////////////////////////////////////
//												T�R E� �S�M� B�LD�R�MLER�
// C'de typedef keywordunu kullan�yorduk. Bu CPP'de hala ge�erli. Modern CPP ile yeni bir t�r-e� ismi tan�mlama yolu eklendi.
	// using keyword�. Fazlas�yla overload edilmi� bir keyword. Yani her using kullan�m� ayn� anlama gelmeyebilir.

using namespace std; 
using IPTR = int*
// mesela yukar�daki iki using kullan�m� ayn� de�il.

// C'de strcmp fonksiyonu i�in e�-t�r ismi;
typedef int (*FCMP)(const char*, const char*);
// CPP'de ayn�s�n� yazal�m
using FCMP = int (*)(const char*, const char*);

using INTR = int&; // INTR, intref t�r�nde bir alias oldu.
using intrefref = int&&;
int main(void) {
	int x = 10;
	INTR& r = x; // aha reference collapsing durumunun oldu�u bir yer daha.
					// & & -> & bundan dolay� int& r = 10 olur;

	intrefref r = 10; // first init yap�lan ifadenin value categorysi PR value oldu�u i�in
						// ve intrefref yerine int&& oldu�u i�in int&& r = 10; ile ayn� anlama gelir.

	intrefref& r2 = 10; // sentaks hatas� ��nk� && vs & -> T& t�r�ne collapse olur. Fakat, first init. yapan 
							// de�i�kenin value categorysi PR value oldu�u i�in sentaks hatas�na sebep olur.

	intrefref&& r2 = 10; // bu sentaks hatas� de�il, && vs && -> && t�r�ne collapse olur. �lk de�er de PR value kategorisinde
							// oldu�u i�in s�k�nt� yok.
}

// bir type(t�r) yazabildi�imiz yerde decltype ile ��kar�m� yap�lan t�r� kullanabiliriz.
// de�i�ken tan�mlamaya gerek yok! auto da ise de�i�ken ile tan�mlamak gerekiyordu. auto x = 10; gibi
struct Oguz {
	int x;
	double* p;
};
int main(void) {
	//decltype(10)
	//decltype(x)
	//decltype(x + 5)
	//decltype(x.y)  
		// bu yukar�dakilerin hepsi birer T�R. T�r gereken her yerde kullan�labilir. HER YERDE DERKEN �AKA YOK

	// decltype'�n iki ayr� kural seti var.
		// 1 - decltype'�n operand� isim formunda olmak zorunda.
			// decltype(x), decltype(y), decltype(a.y), decltype(a->y) gibi
			 
			
		// 2 - decltype'�n operand� isim formunda de�ilse uygulanan kural seti.
			// decltype((x)) <- bunun anlam� farkl�, decltype(x + 5), decltype(10) bunlar 2. kural setine giren k�s�m.


	int x{};
	const int y{ 435 };
	int& r = x;
	int arr[30]{ 0 };
	decltype(x); // -> decltype burada int t�r�nde. Art�k decltype'� tan�mlama ihtiyac�m yok. Fonksiyon geri d�n���nde
					// bile kullan�labilir. decltype(x) foo(int); gibi gibi
	int* p = &x;	
	decltype(p); // int*
	decltype(y); // const int
	decltype(y) t; // hop sentaks hatas�, ��nk� const ifadeler initialize edilmek ZORUNDA. 
	decltype(r); // int&
	decltype(arr); // int[30]
	decltype(arr) r{ 0 }; // int r[30];
	//////////////
	Oguz myoguz;
	Oguz* oguzptr = &myoguz;
	decltype(myoguz.p); // double* t�r�nde.
	decltype(myoguz.x); // int t�r�nde.
	decltype(oguzptr -> p); // double* t�r�nde.

	////////////////
// decltype(expr)
	// value category of expression 
	// e�er	elde edilen t�r�n value categorysi PR ise, T t�r�nde olur.
		//decltype(x) -> int olur.
	//e�er elde edilen t�r�n value categorysi L ise, T& t�r�nde olur.
		// decltype((x)) int& olur
	//e�er elde edilen t�r�n value categorysi X ise, T&& t�r�nde olur.
	/*
	
	De�er kategorisi		decltype sonucu	
	PR							T
	L							T&
	x							T&&		

	*/
}
int main(void) {
	int x = 10;
	int* ptr = &x;
	int arr[10]{ 0 };
	decltype(5); // PR value yani int olacak t�r�
	decltype(x); // PR value yani int olacak t�r�
	decltype(+x); // PR value yani int olacak t�r�
	decltype(x++); // PR value yani int olacak t�r�
	decltype(++x); // L value yani int& olacak t�r�
	decltype(*ptr); // L value yani int& olacak t�r�, ptr burada x'i i�aret ediyor, o da L value oldu�u i�in intref
	decltype(arr[3]); // L value, ��nk� a[3] L value categorysinde
	decltype((x)); // isim formundan ifade formuna ge�iyor, bundan dolay� da int& t�r� olur. -> T&
}

int foo2();
int& bar2();
int&& baz2();

int main(void) {
	foo2(); // bu PR value, e�er bir fonksiyonun geri d�n��� referans de�il ise PR value
	bar2(); // geri d�n�� de�eri ref oldu�u i�in bu L value,
	baz2(); // bir fonksiyonun geri d�n�� t�r� de�eri sa� taraf referans t�r� ise, o fonksiyona �a�r� yap�lan
				// ifadenin value categorysi X value.
	decltype(foo2()); // PR value, int
	decltype(bar2()) r = x; // L value oldu�u i�in x'e ref olabiliyor. �rnek onu g�steriyor
	decltype(baz2()); // X value, int


	decltype(baz2()) r2 = x; // sentaks hatas� ��nk� r2 R value int&& t�r�nden, x ise L value o y�zden.
	decltype(baz2()) r2 + 3= x; // s�k�nt� yok.

	// unevaluated context: i�lem kodu �retilmemesi durumu C'de sizeof'un operat�r�n� kod �retilmiyordu.
		// mesela sizeof(x++) yapt���m�zda x'in de�eri bir artmaz.
	// Ayn� durum decltype'�n operand� i�inde ge�erli. decltype'�n operat�r� i�in i�lem kodu �retilmez. �rnek;
	int x(44);

	decltype(x++);

	std::cout << x << endl; // Yukar�daki bilgiye g�re, decltype'�n operand�na i�lem kodu �retilmeyece�i i�in, ekrana 44 yazd�r�l�r.
								// var ise side affect o ger�ekle�meyecek

	int* pptr = nullptr;
	int x2{};
	decltype(*pptr) yT = x2; // 1- Sentaks hatas� var m�?, 2- T�r� ne?, 3- UB var m�?
								// 1- Sentaks hatas� yok.
								// 2- T�r� int&, ��nk� *pptr bir bellek blo�una i�aret eder. Ve bellek blo�una
									// i�aret etmesinden dolay� her zaman int& t�r�n� d�nd�r�r. E�er deref etmeseydik int* t�r� olacakt�.
								// 3- UB var gibi duruyor ilk bak��ta ama YOK. ��nk�, decltype(*pptr) ifadesindeki *pptr i�in i�lem kodu
									// �retilmeyece�i i�in nullptr deref edilmeyecek, bundan dolay� da UB olu�mayacak.
	decltype(pptr) yt2 = x2; // pptr burada deref edilmedi�i i�in decltype int* t�r�n� al�yor. x2, bir adres olmad��� i�in
								// sentaks hatas� oluyor.
}