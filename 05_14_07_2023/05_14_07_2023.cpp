/*
scope(kapsam)
	Compile time'da yap�lan bir i�lem.
	Identiers � ele alan bir kavram.
	Scopes in C
		-File scope, bildirildi�i dosyan�n tamam�nda kullan�lanlar.
		-Block scope
		-Function prototype 
		-Function scope (goto labellar� function'�n her yeridne kullan�labilir) 
	Scopes in CPP
		-namespace scope (bu file scope'u da kaps�yor)
		-block scope
		-Function prototype 
		-Function scope 
		-Class scope (CPP ile gelen scope)

	name lookup: Compile timeda yap�l�r. Derleyici, kodu anlamland�rmak i�in kodtaki isimlerin hangi varl�klara
					ait oldu�unu anlamak i�in yap�yor bu i�lemi.

	name lookup
		a)ba�ar�l� olabilir
		b)ba�ar�s�z olabilir (ba�ar�s�z olursa sentaks hatas�)
			context control(check) -> legalite kontrol -> mesela bir fonksiyona de�er atamas� yapmaya �al��mak
					int foo(int); // veya kullan�lan ismin ge�erli olup olmad���n� kontrol etme. foo(int) adl� bir fonksiyon varken, foo adl� bir de�i�kene atama yaparsak sentaks hatas� verecek.
					foo = 5; // name lookup foo'yu bulacak, fakat context control enseye vuracak.
				access control -> kullan�l�p kullan�lmayaca��n�n kontrol�, public private vs
�sim arama bir s�ra dahilinde  yap�l�r.
	- �nce kullan�ld��� blo�un i�ine bak.
	- Bulunamazsa, onu kapsayan blo�(klara)a bak
	- Global namespacede araa
Aranan isim bulununca sona erer. 

C'de name lookup ba�ar�s�z olmas� aranan ismin bulunamamas� demek.
CPP'de de ayn� duruma ek olarak bir durum daha var.
	Ambiguity, deniyor buna. Ayn� ismin  birden fazla kez bulunmas�. E�er derleyici, hangi ismin kullan�laca��na dair bir kriter yapamaz ise
		bu hatay� veriyor.
*/

int x = 5;



int main(void) {
	int x = 10;

	x = 6; // bu x 44. sat�rdaki x'e i�aret ediyor namelookup kurallar�ndan dolay�. 
				// derleyici 39 sat�rdaki int x = 5; deyimini maskeliyor/gizliyor. Name masking

}
//////////////////////////////////////////////////////////////////////////

					/*														Scope Resolution Operator ::														*/

// Scope resolution operat�r� tek bir ama�la kullan�lm�yor.
/*
- Unary Operator olarak kullan�labilir.
	::x (e�er scope resolution operat�r� unary prefix olarak kullan�l�rsa global namespacede aranmas� gerekti�ini s�yl�yor)
		46. sat�rdaki x atamas�n� global olan x'e yapmak isteseydik ::x=6; yazmam�z gerekecekti.
- Binary Operator olarak kullan�labilir.
	a::b

Qualified Name(Nitelenmi� �sim): Bir ismin qualified isim olmas� i�in a�a��daki operat�rlerin operand� olmal�.
	- a.b (nokta operat�r�)
	- a->b (arrow operator)
	- ::a (unary resolution operator)
	- a::b (binary resolution operator)
	Yukar�dakilerin hepsi member selection operator
Unqualified Name: E�er member selection operat�rler kullan�lmad�ysa, yal�n olarak yaz�ld���nda denir.


*/
int y = 10;
int z = 32;
int main(){
	int y = 20;
	int z = z; // Bu undefined behaviour. Burada ilk de�er verme i�lemi global namespacedeki 32 de�eri ile de�il. B�yle olma sebebi de
					// atama operat�r�n�n sa��na ge�ti�imizde art�k int z'nin scopu i�erisinde oldu�umuz i�in, asl�nda z'ye kendi de�eri(garbage value) ile atama yap�yoruz.
						// Bundan dolay� da undefined behaviour oluyor.
	// bunu fonksiyon tan�m� olarak d���n
	//	void foo(int foo); -> mesela burada UB yok ��nk� parametrenin bulundu�u  scope farkl�
	y = 30; // main blo�u i�erisindeki y'nin de�erini 30 yapar.
	::y = 12312; // global namespacedeki y'nin de�erini 12312 yapar.
}

void foo(int foo) {
	foo(foo); // buna bak�nca sanki recursive function gibi duruyor FAKAT DE��L! �sim arama kurallar�na g�re, foo burada fonksiyonun ad� m� yoksa parametre de�i�keninin ad� m�?
				// tabiiki de parametre de�i�keninin ad�. Parametre de�i�kenlerinin scope'u fonksiyonun g�vdesi i�erisinde. Bundan dolay� sentaks hatas�!
					// Ek olarak, parametre ismi block scopeta iken, fonksiyon ad� file scopeta.

	::foo(foo); // b�yle recursive yap�labilir. Unary Scope resolution operator kullan�larak
}

int main(void)
{
	int x = 10;
	if (x > 5) {
		double x; 5.;
		x = 40; // 97. sat�rda tan�mlad���m�z double x, int x'i maskeler. 
					// bu maskeleme i�ini engellemek i�in bir ara� yok :/ ��nk� ikisi de main blo�u i�erisinde,. Unary scope res. ancak global i�in i� yap�yor.
	}
}
//hat�rlatma
// source file: preprocessor direktiflerinin yap�lmad��� oldu�u yer.
// Translation unit: Derleyicinin g�rd��� kodun ��kt��� yer, preprocessor direktifleri burada yap�lm�� oluyor.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

													/*						ODR(One Definition Rule)						*/
/*																				Tek tan�mlama Kural�
	- Varl�klar�n bir proje i�erisinde sadece bir kere tan�mlanma haklar� vard�r. Farkl� dosyalarda bile olsalar, ayn� proje i�inde bulunuyorlar ise ODR kural�n� �i�nemi� oluruz.
	- Her declaration bir definitionn de�ildir ama her definition bir declarationdur.
	- Fonksiyon ve global de�i�kenlerin proje dahilinde birden fazla tan�mlamas� OLAMAZ. 

�stisna durumlar:
	- inline function
	- inline variables
	- constexpr functions
	- template definitions 
*/


													/*						Inline Functions								*/
/*
Inline expansion: Derleyicinin kulland���, en etkili, optimizasyon tekniklerinden biri.
	- Kodu as-if(�yleymi� gibi) derliyor. Bu sayede koda optimizasyon sa�l�yor.
		�yleymi� gibi derken asl�nda kodun de�i�tirilmesi olay� var ama observable behaviour de�i�miyor! Diyelim ki d�ng� i�erisinde, 3 defa, ekrana "hello, world" yazd�ran bir program var.
			Derleyici for d�ng�s� kullanmak yerine d�ng� olmadan ekrana 3 defa yazd�rarak kaynaklardan tasarruf edebilir. Bunun gibi de�i�iklikler. Daha karma��k i�lemler de var tabii.
	
	- Tan�m g�r�lmek zorunda. Derleyici, kodu g�rd�kten sonra bir analizden ge�irir ve duruma ba�l� olarak inline expansion optimizasyonunu uygular. 
		�yle kafas�na g�re "aa hadi burada optimizasyon" yapay�m demez. Baz� durumlarda inline expansion, less-efficient code �retimine sebep olabilir.

	- Derleyici yapabilirse. Derleyici tan�m� g�r�p analiz ettikten sonra inline expansion yap�labilir oldu�una karar verse dahi optimizasyonu yapamayabilir. Bu, derleyiciyi
		kodlayan ki�ilerin yeteneklerine ba�l�.

	- Inline expansion switch: IDE'lerin "force inline expansion" gibi a��l�p kapat�labilen �zellikleri olabilir. Hoca �ok �st�nde durmad� �yle bilgi olsun diye verdi. 
 

	Inline function ile inline expansion kar��t�r�ld��� i�in ilk expansionu g�rd�k ki function ile kar��t�rmayal�m.
------------------------------------------------------------------------------------------------------------------------------------------
Inline functions

- Bir fonksiyonun inline anahtar s�zc��� ile tan�mlamas�, inline expansion ile alakal� hi�bir de�i�ikli�e sebep olmuyor.
- Birden fazla kaynak dosyas�da inline fonksiyonlar �zde� olarak tan�mlan�rsa ODR ihlal edilmez. B�t�n tokenlar� ayn� olmak zorunda!

//	engin.cpp
	inline int sum_square(int a, int b){
		return a * a + b * b;
	}
//	ali.cpp
	inline int sum_square(int a, int b){
		return a * a + b * b;
	}
- Inline fonksiyonu kodu k���k ve fonksiyonlar�n bir �ok kez �a�r�ld��� projelerde kullanmak daha mant�kl�. Her fonksiyonu inline tan�mlamak iyi bir fikir de�il.
	e�er fonksiyonun i�erisinde ba�ka bir ba�l�k/kaynak dosyas�ndan al�nan bir de�i�ken veya de�i�ken s�n�f� kullan�l�yorsa bu ilave ba��ml�l�klara/dezavantajlara yol a�abilir.
		inline keywordunu kullanarak bu fonksiyonlara inline expansion yap�lmas�na OLANAK sa�l�yor. GARANT� de�il.
- Niye inline fonksiyon yap�yoruz? Fonksiyona yap�lan �a�r�lar i�in derleyiciye inline expansion OLANA�I kazand�rmak i�in. E�er inline keyword�n� kullanmasayd�k
	derleyici fonksiyonun tan�m�n� g�remeyecekti sadece bildirimini g�recekti.
	inline int sum_square(int a, int b) -> b�yle olunca tan�m�n� g�r�yor
	int sum_square(int a, int b) -> b�yle olunca tan�m�n� g�rm�yor(farkl� dosyada ise, mesela bir header file i�erisinde olabilir)
		e�er bu fonksiyonu ayn� �ekilde al�p di�er kaynak dosyas�na yap��t�rsayd�k bu seferde ODR'� �i�nemi� olacakt�k.

- Diyelim ki bir ba�l�k dosyas�nda bir inline fonksiyon tan�mlad�k. Bu fonksiyonu 5 ayr� kaynak dosyas�nda kullan�yoruz. Her bir kaynak dosyas�nda tekrar tekrar compile edilmesindense
	compile edilmi� fonksiyonun adresi kullan�l�r. BU GARANT�
- E�er derleyici bir fonksiyonun hem declarationunu hem definitionunu g�r�yor ise, bu fonksiyonlardan birisinin inline olmas�, o fonksiyonun inline fonksiyon olmas� i�in yeterli.

	inline int foo(int x, int b){
		return x + b;
	}
	int foo(int x, int b){
		return x + b;
	}
	// hepsini tek tek yazmaya ��eniyorum o y�zden k�saca;
		- inline int, int �eklinde olsa bile inline fonksiyon
		- int, inline int �eklinde olsa bile inline fonksiyon		
		-  inline, inline �eklinde olsa bile inline	fonksiyon


- C++17 standart� ile yeni bir �zellik eklendi.
	inline keywordu global de�i�kenlerin tan�m�na da eklendi. Bunlara 'inline variable' denildi.
		Inline functions ile temel ili�kisi ayn�.
- E�er bir de�i�ken inline variable olarak tan�mlan�rsa ve birden fazla kaynak dosyas�nda �zde� olarak yer al�rsa, ODF �i�nenmemi� oluyor. Ve di�er kaynak dosyalar�nda yer alan
	inline variables ayn� de�i�ken oluyor.

		#engin.cpp
		inline int x = 10;
		#ali.cpp
		inline int x = 10;
		#nec.cpp
		inline int x = 10;
	x bir inline variable. 3 ayr� kaynak dosyas�nda �zde� olarak(b�t�n tokenlar� ayn�) tan�mlanm��. Bu asl�nda C'deki extern keyword� gibi. Bu tan�mlar
		ayr� kaynak dosyalar�nda olsa bile hepsi ayn� de�i�kenden bahsediyor.(adresleri ayn� yani) 7 kocal� h�rm�z gibi. Kocalar�n hepsi farkl� insanlar ama kar�lar� ayn�(�rne�e bak :/ )

inline int& foo(){
	static int x = 10;

	return x;
	// bu fonksiyon asl�nda �akall�k i�eriyor. Fonksiyonun geri d�n�� de�erini l value referans yap�yoruz ve fonksiyonun i�erisinde static bir de�i�ken tan�ml�yoruz.
		// tan�mlad���m�z bu de�i�kenin referans�n� geri d�nd�r�yoruz. Bu sayede her kaynak dosyas�ndan eri�ilebilen bir de�i�ken tan�mlam�� olduk. inline variable gibi
			// ama inline fonksiyon ve referans semanti�ini kullanarak. Bu �akall��� ekstra bir .h .cpp istemiyor isek yap�yoruz fakat g�n�m�zde buna 'inline variable' sayesinde ihtiya� yok
	
}

- Inline variables ile header only proje yapma �ok kolay hale geldi.
*/
													/*						NUMARALANDIRMA T�RLER�(enum)						*/
/*
- C dilinde enum t�r� int ile cast ediliyor. CPP'de ise underlying type yani derleyici karar veriyor. 

Istenmeyen durumlar;
- �rt�l� d�n���mler:
	Modern CPP �ncesi, numaraland�rma t�rlerinden aritmetik t�rlere �rt�l� d�n���m var iken aritmetik t�rlerden numaraland�rma t�rlerine �rt�l� d�n���m yoktu.
		Bu yanl�� koyulmu� bir kural. 
		enum Color{
			White, Gray, Blue, Black
		};
		enum Pos{
			On, Off
		};
		int main(){
			Color mycolor;
			mycolor = 12; // sentaks hatas�
			mycolor = Off; // sentaks hatas�

			Color mycolor_2 = Blue;
			int x = mycolor_2; // legal ama bu bir ihmal. Necati hoca bunun legal olmamas� gerekti�ini s�yl�yor. CPP'nin gen�lik g�nahlar�ndan biriymi�, allah affetsin diyelim.
				//typecast operat�rleri kullan�larak bu d�n���mlerin yap�lmas� normal. typecast olmadan �rt�l� d�n���m ile yap�ld���nda bir problem ortaya ��kt���nda
					// problemi bulman�n zor oldu�undan bahsetti hoca.
		}
- Underlying-type: Underlying type, derleyiciye ba�l� oldu�u i�in incomplete type olarak kullan�lam�yor.
	enum Color;
	struct Engin{
		//..
		Color myvar; // bu struct�n complete olabilmesi i�in Color t�r�n�n sizeof de�eri bilinmek zorunda.
						// enum lar�n t�rleri de underlying type oldu�u i�in bu de�er herhangi bir �ey olabilir.
							// Color'�n sizeof'u belli olmad��� i�in buras� sentaks hatas�.
	}

- Scope kavram�ndan dolay� s�k�nt� olabiliyor. enum'�n elemanlar�n�n scope'u, enum un tan�m�n�n yap�ld��� yerdir.
	Yani i�erisindeki elemanlar�n ayr� bir scopeu yok. enum global namespacede ise elemanlar� da ayn�. Bundan dolay�
		ba�ka bir enum eleman� veya ba�ka bir t�r�n eleman� ile �ak��abilir, bu sentaks hatas�.
engin.h
	enum Color{White, Gray, Red}; 
ali.h
	enum ScreenColor{Magenta, Red, Black}; 
Bu yukar�daki iki .h dosyas�n� ayn� kaynak dosyas�na include etti�imizi d���nelim. Color ve ScreenColor iki ayr�
	identifier olsa da scopelar� ayn�. Ayn� zamanda enum'un elemanlar�n�n scopeuda ayn�. �kisinde de Red, Black oldu�u
		i�in bu program� derledi�imizde derleyici sentaks hatas� verecek.

Bu yukar�daki sorunlar� ��zmek i�in programc�lar baz� teknikler kullan�yorlard�.
- enum ad�n� ve elemanlar�n�n ad�n�n ba��na, sonuna belirleyici bir ek getiriyorlard�
	enum TextWindowColor {TextWindowColorRed, TextWindowColorWhite}; 
- Ayr� isim alan�(namespace) i�ine almak. Veya ba�ka s�n�flara nested olarak almak.

Sorunlar� ��zmek, kurallar� d�zenlemek yerine yeni kural eklemi�ler. avg T�rkiye
--------------------------------------------------------------------
- Bildirimini yaparken enum'�n underlying type'�n� kendimiz belirleyebiliyoruz. column token�n� kullanarak.
	Art�k ikinci probleme bir ��z�m�m�z var. Struct art�k Color'�n sizeof de�erini bilece�inden dolay� sentaks hatas� de�il.
	enum Color : 'underlying-type' {Red, Green, Blue};
	enum Color : unsigned int {Red, Green, Blue};

- enum class diye yeni bir �ey eklendi. Standart buna scoped enum(kapsamland�r�lm�� enum) diyor. 
	Eski enum t�r�nden bahsetmek istersek 'unscoped enum' veya 'traditional enum' diyebiliriz.
	enum class ile beraber kapsamland�r�lan enum'�n kullan�m �ekli de de�i�ti. Ayn� zamanda art�k ba�ka .h dosylar�ndan gelen
		veya ayn� kaynak dosyas�nda bulunan benzer enum elemanlar�n�n art�k �ak��ma durumu ortadan kalkt�. (239. sat�r)

	enum class Color : unsigned char {Green, Red, Blue};
	int main(){
		Color mycolor = Blue; // Bu sentaks hatas�. Kapsam�nda de�iliz. Burada scope resolution operat�r�n� binary
								// infix olarak kullanmam�z gerekiyor.
		Color mycolor = Color::Blue; // bu ge�erli, scope resolution sayesinde eri�ebiliyoruz
	}
----------------------------------------------------------------------------
// traffic.h
enum class TrafficLight {Red, Amber, Green};
// widget.h
enum class ScreenColor {White, Gray, Red, Blue, Black};		
	int main(){
		Trafficlight tl = TrafficLight::Red;
		int x = tl; // e�er bu geleneksel enum olsa idi �rt�l� d�n���m olaca��ndan dolay� legal olacakt�.
						// fakat enum class bunun �n�ne ge�iyor ve CPP gen�lik hatas�n� d�zeltiyor. Hangimiz hata yapmad�k
							// E�er bilerek, isteyerek bu d�n���m� yapmak istiyorsak type-cast operat�r� kullanabiliriz.
		int z = static_cast<int>(tl); // type-castlerden bir tanesi. Daha g�rmedik.
	
	}
-----------------------------------------------------------------------------
- Scoped enum'�n dile eklenmesi ile beraber bir �ok problemi ortadan kald�rsada ba�ka bir probleme sebep oldu.
	Verbosity(V), Verbose(adj) diye bir kavram. Hoca bundan kod kalabal��� olarak bahsetti. Kodun genel g�r�n���n�n, okunu�unu zorla�t�rd���n� s�yl�yor.
	
	enum class Suit {Club, Diamond, Heart, Spade};

	void func(Suit x){
		Suit::Club; // b�t�n bildirimlerde, tan�mlarda b�yle kullan�dl���n� d���n. �ok fazla g�z yoracak.
						// bunun �n�ne ge�mek i�in bir standart eklenmi�
		using enum Suit; // Bulundu�u scopetaki enumlar� nitelendirilmi� enum olarak kullanma zorunlulu�unu kald�r�yor.
		x = Club; // art�k Suit::Club yazmam�za gerek yok. C++20 ile eklendi.
		auto y = Diamond; 
	-------------------------------------------------------- A�a��daki �rnek i�in yukar�daki using enum'� g�rmezden gel
	// Diyelim ki �ok b�y�k bir enum class'�m�z var. Fakat biz bunun i�inden sadece 1-2 tanesini nitelendirilmemi�
		// olarak kullanmak istiyoruz.
		using Suit::Diamond; // Bu bildirim ile, kendi scope'unda ilgili enumarat�r�n Diamond adl� eleman�n� kullanabiliyoruz.
		auto z = Diamond; // legal
		auto x1 = Spade; // sentaks hatas�, Spade'e eri�emeyiz.
	}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
													/*					TYPE CAST OPERATORS					*/
/*
- (d�n���m�n yap�laca�� t�r)de�i�kenin ad� = (dval)int_expr;
- 


*/



/*
int main(){
	int x = 10;
	const int* p = &x; // x'in kendisi const de�il, biz b�yle tan�mlayarak p �zerinden de�i�iklik
							// yap�lmas�n� istemiyoruz.
	// int* ptr = p; // b�yle yazarsak hata verir ��nk� const int* t�r�nden int* t�r�ne atama yap�lmaya �al���l�yor
	int* ptr = (int*)p; // �imdi s�k�nt� yok, hem de UB'de olmaz bu �ekilde.  Normalde const int* olan bir nesnenin
							// �zerinde de�i�iklik yapmak s�k�nt� ama x'in kendisi const olmad��� i�in s�k�nt� yok.
								// e�er const int x = 10; olsayd� UB vard�, 

	// Kodun derleyici taraf�ndaki sentaks hatas�n� bu �ekilde d�zeltebiliriz. Fakat, bunu yaparken ayn� zamanda
		// yap�lan d�n���m�n compatible olup olmad���na da bakmak gerekir.
	int z = 12;

	float* fz = (float*)(&z); // evet sentaks hatas� yok ama bu kod yaln�z. int ile float compatible type de�il.


}	


*/