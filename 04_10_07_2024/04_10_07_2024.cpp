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
{								// default parametreye sahip olmasý demek 3. parametrenin sadece 10 deðerini almasý demek deðil.
									// 3. parametreye eðer bir deðer gönderilmez ise 10 deðerini alacak demek. default argument aslýnda bu anlama geliyor.
								// default argument programýn derleme zamanýnda kullanýlan/belli olan bir araç
	std::cout << "a = " << a << "  b = " << b << "  c = " << c << std::endl;
}
int main(void) {
	foo(31, 52, 69); // ekrana 31, 52, 69 yazdýrýr
	foo(31, 52);	// ekrana 31 52 10 yazdýrýr
	foo(31);		// ekrana 31 20 10 yazdýrýr
	foo();			// ekrana 30 20 10 yazdýrýr
}
// referans ve pointelar da default argument olabilirler.
int x = 10;
int fooptr(int* p = nullptr, int* p2 = &x);
int fooref(int& b = x);
// default argümanýn constant bir ifade olma zorunluluðu yoktur. 
int bar(int x = fooptr()); // legal, default deðer baþka bir fonksiyonun dönüþ deðeri olabilir.


void func(int *= &x); // burada derleyici hata veriyor, bunun sebebi maximal munch kuralý.
	// parametre tokenlarýna ayrýldýðýnda  parametreyi int* türü olarak deðil int türünden bir ifadeye
		// atama iþlemi yapýyor (deðeri adres g ile çarpýyor)

void func2(int* a = &x); // isim verdiðimizde bu durum ortadan kalkýyor tabii.
	// fonksiyon parametrelerini isimlendirmesek bile kabul oluyor. C'de gördük bunu


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
	baz(func3()); // ekrana 1 yazdýrýr 
	baz(func3()); // ekrana 2 yazdýrýr
	baz(func3()); // ekrana 3 yazdýrýr
}
//////////////////////////////////////////
void funct(int x, int y = x); // bu geçerli deðil, bir parametrenin default deðeri kendisinden önceki parametre olamaz.


int print_date(int day = -1, int month = -1, int year = -1) // Bazý fonksiyonlarda default deðerin kullanýlýp kullanýlmadýðýný
// anlamak için default deðer kullanýlýyor. Tabii bu kullanýlmayan deðerin
// nasýl yorumlanacaðý dökümantasyonda belirtilmek zorunda.
// mesela bu fonksiyon için eðer argüman almýyor ise, güncel tarihi kullanýyor olabilir. 
// implementasyona baðlý. Dökümantasyonda belirtilir.

///////////////////////////////////////////////////////////////////////////
/*                                                     auto type deduction                                                       */

int x = 10;
auto int x = 10; // bu iki ifade C dilinde ayný, auto burada x'in otomatik ömürlü olduðunu belirtiyor. Modern CPP'de sentaks hatasý


// Modern CPP'de place holder olarak görev yapýyor. Derleme zamanýnda belli olur.
// Type deduction auto keywordü karþýlýðýnda yapýlýr. auto bir type holder olarak görev yapar ve derleyici auto yerine gelecek
	// türü anlar.
// auto'nun türü anlaþýldýðýnda deðiþkeninde türü anlaþýlabilir.
	// auto'ya karþýlýk gelen tür ile deðiþkenin türü ayný olmak zorunda deðil.
// auto ile default init yapýlamaz. Copy ya da direct init olmak zorunda
// Bu iki þeyi bilmiyorsan kapat pcyi git öðrenme cpp
	//- Ýfadenin türü
	// - Ýfadenin deðer kategorisi

	// Value category ifadeyi niteler.
int x = 10; // x'in deðer kategorisi ne? eðer L value - R value diyorsan YANLIÞ!
// bir deðiþkenin value categorysi olmaz. x'in sadece data type'ý olur.

/* Eðer þöyle yazarsak;
	x; ahanda þimdi value categorysi var ve l value
	+x; PR value
	Uzun lafýn kýsasý, eðer bir deðiþken tanýmlýyorsak onun kategorisi deðil veri türü var.
	int x = 10; -> veri türü var(int), deðer kategorisi yok.
	x; -> deðer kategorisi var
	int* y = nullptr; veri türü var(int*)
	int& r = x; // deðer türü int& (intref)
	y; -> veri türü int*
	x -> veri türü int
	peki ya r; ifadesinin veri türü ne? int& diyorsan enseye þaplaðý yedin
	r; -> bunun veri türü int. Çünkü bir ifadenin türü ref(&) türünden olamaz.

*/



int main() {
	auto x = 10; // auto'nýn kullanýlabilmesi için ya direct ya da copy olarak init edilmesi ZORUNLU!
	// auto x(10); direct init, üstteki de copy init.	
	// auto'ya karþýlýk gelen deðer, initializer expressiondan anlaþýlacak. 
//////////////////////////////////////////////
// Eðer ilk deðer veren ifade const bir ifade ise constluk düþer.

const int xyz = 10;
auto autox = xyz; // bunun veri türü const int deðil sadece int

int x1 = 10;
int xref = x1;

auto kz = xref; // bu int& deðil sadece int
kz = 999; // yapýldýðýnda sadece kz'nin deðeri deðiþir, intref olsaydý x1'de deðiþirdi.

int ar[5]{};
auto autoarr = ar; // ar burada array decaye uðrar. Bundan dolayý autoarr'nin veri türü int* türünden olur
const int ar[5]{}; // böyle olduðunda ise autoarr, const int* türüne dönüþecek. 
//////////////////////////////
auto p = "Kadeh"; // Kadek string literali olduðu için -> const char[6];
					// ve burada array decay olacaðý içinde p'nin veri türü -> const char* 
}

int foo(int);
int main(void) {
	auto x = foo; 
	// auto x = &foo; -> function to pointer conversion uygulandý, ondan sonra tür çýkarýmý yapýlýyor.
	// x'in türü int (*)(int) türünden olacak. Fonksiyon iþaretçisi
	// int (*x)(int)
}

// AUTO &IDF = EXPR; -> REFERANS var ise ne olur?

/*
- Her zaman lvalue expression olmak zorunda.
- const düþmüyor
- array decayde uygulanmýyor
int foo(int); -> foo'nun türü int(int)
	// eðer function to pointer conversion olur ise int (*)(int) olur.
int main(void){
	int x = 6;
	auto &r = x; -> bu int& r = x; 
	// auto &r2 = 10; -> sentaks hatasý, rvalue ile init edemeyiz.
	////////////////
	const int x2 = 10;
	auto &r2 = x2; -> const int& r2;
	int arr[5] = {1, 2, 3, 4, 5};
	auto &x = arr; -> array decay uygulanmadýðý için int[dizinin_boyutu] veri türünü alýr.
	// dizi const olursa da "const int (&x)" olurdu.
	
		auto a = "Oguz"; // bu const int* veri türünü alacak
	auto& a2 = "Oguz"; // bu ise const char[5] veri türünü alacak. Çünkü auto&'te array decay olmuyor.

	auto fx = foo; // böyle yazýlýras function decayden dolayý fx'in türü
					// int (*fx)(int) olur. 
	auto& fx = foo; // ref olunca decay olmuyordu, bundan dolayý int(&r)(int) olacak fx'in veri türü.
						// function reference oldu Ü
}
*/

///////////////////////////
// auto&&

double bar();

int main(void) {
	int x = 10;
	auto&& r = x; // forwarding/universal reference 
	// Her türle veya herhangi bir deðer kategorisi ile ilk deðer verilebilir.
	r = x; // l-value alýr
	r = x + 5; // r-value de alýr
	// Eðer ilk deðer veren ifade l-value expression ise
		// autoya karþýlýk gelen çýkarým int&& olacak. ÖNEMLÝ!! Bu karþýlýk r deðil auto için;
			// int& &&r; veri türü haline gelecek.
			
	// Eðer ilk deðer veren ifade r-value expression ise
		// autoya karþýlýk gelen çýkarým int olacak. ÖNEMLÝ!! Bu karþýlýk r deðil auto için;
			// int &&r; veri türü haline gelecek. (r value reference)
			
	// yukarýdaki iki örnekte reference to reference oluyor. Normalde reference to reference diye bir þey yok fakat
		// burada özel bir kural uygulanýyor. Bu kurala da 'reference collapsin' deniyor.

	// L value auto ===> T&
	// R value auto ===> T

	reference collapsing
	// & -> sol referans, && - sað referans
		// Bu tabloda referansa bakarken first init. yapýlan ifadenin deðer kategorisini de ele almak zorundasýn.
			// Eðer senin sol tarafýn referansý L value ise, first init. deðerin R ise bu sentaks hatasý olur.
				// tür eþ isimi bildirimleri kýsmýnad örnek var. intrefref &r2 olan örnek
	REFERANS	REFERANS	SONUC REFERANS
	--------------------------------------
	&				&&			&
	&				&			&
	&&				&			&
	&&				&&			&&
		// T -> tür/type anlamýnda.
// Yukarýsý biraz karýþýk oldu. && (universal referencing) her iki deðer kategorisini bünyesine alabiliyor.
	// Aldýðý deðer kategorisine göre auto'nün tür çýkarýmý yapýlýyor. Eðer, auto L-value deðer kategorisine ait bir
		// deðer ile first init. edilir ise T& çýkarýmý yapýlýyor. Bu yapýlan çýkarým auto için deðiþkenin kendisi
			// için deðil. int& &&r þeklini alan ifade sol ref + sað ref olduðu için sonuç referanslarý sol ref oluyor.
				// reference collapsing dediðimiz bu. Herhangi çýkarýmdan birisinin sol ref olmasý, sonucu sol ref yapar. OR gate gibi
}
////////////////////////////////////////////////////////////
//												TÜR EÞ ÝSÝMÝ BÝLDÝRÝMLERÝ
// C'de typedef keywordunu kullanýyorduk. Bu CPP'de hala geçerli. Modern CPP ile yeni bir tür-eþ ismi tanýmlama yolu eklendi.
	// using keywordü. Fazlasýyla overload edilmiþ bir keyword. Yani her using kullanýmý ayný anlama gelmeyebilir.

using namespace std; 
using IPTR = int*
// mesela yukarýdaki iki using kullanýmý ayný deðil.

// C'de strcmp fonksiyonu için eþ-tür ismi;
typedef int (*FCMP)(const char*, const char*);
// CPP'de aynýsýný yazalým
using FCMP = int (*)(const char*, const char*);

using INTR = int&; // INTR, intref türünde bir alias oldu.
using intrefref = int&&;
int main(void) {
	int x = 10;
	INTR& r = x; // aha reference collapsing durumunun olduðu bir yer daha.
					// & & -> & bundan dolayý int& r = 10 olur;

	intrefref r = 10; // first init yapýlan ifadenin value categorysi PR value olduðu için
						// ve intrefref yerine int&& olduðu için int&& r = 10; ile ayný anlama gelir.

	intrefref& r2 = 10; // sentaks hatasý çünkü && vs & -> T& türüne collapse olur. Fakat, first init. yapan 
							// deðiþkenin value categorysi PR value olduðu için sentaks hatasýna sebep olur.

	intrefref&& r2 = 10; // bu sentaks hatasý deðil, && vs && -> && türüne collapse olur. Ýlk deðer de PR value kategorisinde
							// olduðu için sýkýntý yok.
}

// bir type(tür) yazabildiðimiz yerde decltype ile çýkarýmý yapýlan türü kullanabiliriz.
// deðiþken tanýmlamaya gerek yok! auto da ise deðiþken ile tanýmlamak gerekiyordu. auto x = 10; gibi
struct Oguz {
	int x;
	double* p;
};
int main(void) {
	//decltype(10)
	//decltype(x)
	//decltype(x + 5)
	//decltype(x.y)  
		// bu yukarýdakilerin hepsi birer TÜR. Tür gereken her yerde kullanýlabilir. HER YERDE DERKEN ÞAKA YOK

	// decltype'ýn iki ayrý kural seti var.
		// 1 - decltype'ýn operandý isim formunda olmak zorunda.
			// decltype(x), decltype(y), decltype(a.y), decltype(a->y) gibi
			 
			
		// 2 - decltype'ýn operandý isim formunda deðilse uygulanan kural seti.
			// decltype((x)) <- bunun anlamý farklý, decltype(x + 5), decltype(10) bunlar 2. kural setine giren kýsým.


	int x{};
	const int y{ 435 };
	int& r = x;
	int arr[30]{ 0 };
	decltype(x); // -> decltype burada int türünde. Artýk decltype'ý tanýmlama ihtiyacým yok. Fonksiyon geri dönüþünde
					// bile kullanýlabilir. decltype(x) foo(int); gibi gibi
	int* p = &x;	
	decltype(p); // int*
	decltype(y); // const int
	decltype(y) t; // hop sentaks hatasý, çünkü const ifadeler initialize edilmek ZORUNDA. 
	decltype(r); // int&
	decltype(arr); // int[30]
	decltype(arr) r{ 0 }; // int r[30];
	//////////////
	Oguz myoguz;
	Oguz* oguzptr = &myoguz;
	decltype(myoguz.p); // double* türünde.
	decltype(myoguz.x); // int türünde.
	decltype(oguzptr -> p); // double* türünde.

	////////////////
// decltype(expr)
	// value category of expression 
	// eðer	elde edilen türün value categorysi PR ise, T türünde olur.
		//decltype(x) -> int olur.
	//eðer elde edilen türün value categorysi L ise, T& türünde olur.
		// decltype((x)) int& olur
	//eðer elde edilen türün value categorysi X ise, T&& türünde olur.
	/*
	
	Deðer kategorisi		decltype sonucu	
	PR							T
	L							T&
	x							T&&		

	*/
}
int main(void) {
	int x = 10;
	int* ptr = &x;
	int arr[10]{ 0 };
	decltype(5); // PR value yani int olacak türü
	decltype(x); // PR value yani int olacak türü
	decltype(+x); // PR value yani int olacak türü
	decltype(x++); // PR value yani int olacak türü
	decltype(++x); // L value yani int& olacak türü
	decltype(*ptr); // L value yani int& olacak türü, ptr burada x'i iþaret ediyor, o da L value olduðu için intref
	decltype(arr[3]); // L value, çünkü a[3] L value categorysinde
	decltype((x)); // isim formundan ifade formuna geçiyor, bundan dolayý da int& türü olur. -> T&
}

int foo2();
int& bar2();
int&& baz2();

int main(void) {
	foo2(); // bu PR value, eðer bir fonksiyonun geri dönüþü referans deðil ise PR value
	bar2(); // geri dönüþ deðeri ref olduðu için bu L value,
	baz2(); // bir fonksiyonun geri dönüþ türü deðeri sað taraf referans türü ise, o fonksiyona çaðrý yapýlan
				// ifadenin value categorysi X value.
	decltype(foo2()); // PR value, int
	decltype(bar2()) r = x; // L value olduðu için x'e ref olabiliyor. Örnek onu gösteriyor
	decltype(baz2()); // X value, int


	decltype(baz2()) r2 = x; // sentaks hatasý çünkü r2 R value int&& türünden, x ise L value o yüzden.
	decltype(baz2()) r2 + 3= x; // sýkýntý yok.

	// unevaluated context: iþlem kodu üretilmemesi durumu C'de sizeof'un operatörünü kod üretilmiyordu.
		// mesela sizeof(x++) yaptýðýmýzda x'in deðeri bir artmaz.
	// Ayný durum decltype'ýn operandý içinde geçerli. decltype'ýn operatörü için iþlem kodu üretilmez. Örnek;
	int x(44);

	decltype(x++);

	std::cout << x << endl; // Yukarýdaki bilgiye göre, decltype'ýn operandýna iþlem kodu üretilmeyeceði için, ekrana 44 yazdýrýlýr.
								// var ise side affect o gerçekleþmeyecek

	int* pptr = nullptr;
	int x2{};
	decltype(*pptr) yT = x2; // 1- Sentaks hatasý var mý?, 2- Türü ne?, 3- UB var mý?
								// 1- Sentaks hatasý yok.
								// 2- Türü int&, çünkü *pptr bir bellek bloðuna iþaret eder. Ve bellek bloðuna
									// iþaret etmesinden dolayý her zaman int& türünü döndürür. Eðer deref etmeseydik int* türü olacaktý.
								// 3- UB var gibi duruyor ilk bakýþta ama YOK. Çünkü, decltype(*pptr) ifadesindeki *pptr için iþlem kodu
									// üretilmeyeceði için nullptr deref edilmeyecek, bundan dolayý da UB oluþmayacak.
	decltype(pptr) yt2 = x2; // pptr burada deref edilmediði için decltype int* türünü alýyor. x2, bir adres olmadýðý için
								// sentaks hatasý oluyor.
}
