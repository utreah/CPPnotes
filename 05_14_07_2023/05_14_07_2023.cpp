/*
scope(kapsam)
	Compile time'da yapýlan bir iþlem.
	Identiers ý ele alan bir kavram.
	Scopes in C
		-File scope, bildirildiði dosyanýn tamamýnda kullanýlanlar.
		-Block scope
		-Function prototype 
		-Function scope (goto labellarý function'ýn her yeridne kullanýlabilir) 
	Scopes in CPP
		-namespace scope (bu file scope'u da kapsýyor)
		-block scope
		-Function prototype 
		-Function scope 
		-Class scope (CPP ile gelen scope)

	name lookup: Compile timeda yapýlýr. Derleyici, kodu anlamlandýrmak için kodtaki isimlerin hangi varlýklara
					ait olduðunu anlamak için yapýyor bu iþlemi.

	name lookup
		a)baþarýlý olabilir
		b)baþarýsýz olabilir (baþarýsýz olursa sentaks hatasý)
			context control(check) -> legalite kontrol -> mesela bir fonksiyona deðer atamasý yapmaya çalýþmak
					int foo(int); // veya kullanýlan ismin geçerli olup olmadýðýný kontrol etme. foo(int) adlý bir fonksiyon varken, foo adlý bir deðiþkene atama yaparsak sentaks hatasý verecek.
					foo = 5; // name lookup foo'yu bulacak, fakat context control enseye vuracak.
				access control -> kullanýlýp kullanýlmayacaðýnýn kontrolü, public private vs
Ýsim arama bir sýra dahilinde  yapýlýr.
	- Önce kullanýldýðý bloðun içine bak.
	- Bulunamazsa, onu kapsayan bloð(klara)a bak
	- Global namespacede araa
Aranan isim bulununca sona erer. 

C'de name lookup baþarýsýz olmasý aranan ismin bulunamamasý demek.
CPP'de de ayný duruma ek olarak bir durum daha var.
	Ambiguity, deniyor buna. Ayný ismin  birden fazla kez bulunmasý. Eðer derleyici, hangi ismin kullanýlacaðýna dair bir kriter yapamaz ise
		bu hatayý veriyor.
*/

int x = 5;



int main(void) {
	int x = 10;

	x = 6; // bu x 44. satýrdaki x'e iþaret ediyor namelookup kurallarýndan dolayý. 
				// derleyici 39 satýrdaki int x = 5; deyimini maskeliyor/gizliyor. Name masking

}
//////////////////////////////////////////////////////////////////////////

					/*														Scope Resolution Operator ::														*/

// Scope resolution operatörü tek bir amaçla kullanýlmýyor.
/*
- Unary Operator olarak kullanýlabilir.
	::x (eðer scope resolution operatörü unary prefix olarak kullanýlýrsa global namespacede aranmasý gerektiðini söylüyor)
		46. satýrdaki x atamasýný global olan x'e yapmak isteseydik ::x=6; yazmamýz gerekecekti.
- Binary Operator olarak kullanýlabilir.
	a::b

Qualified Name(Nitelenmiþ Ýsim): Bir ismin qualified isim olmasý için aþaðýdaki operatörlerin operandý olmalý.
	- a.b (nokta operatörü)
	- a->b (arrow operator)
	- ::a (unary resolution operator)
	- a::b (binary resolution operator)
	Yukarýdakilerin hepsi member selection operator
Unqualified Name: Eðer member selection operatörler kullanýlmadýysa, yalýn olarak yazýldýðýnda denir.


*/
int y = 10;
int z = 32;
int main(){
	int y = 20;
	int z = z; // Bu undefined behaviour. Burada ilk deðer verme iþlemi global namespacedeki 32 deðeri ile deðil. Böyle olma sebebi de
					// atama operatörünün saðýna geçtiðimizde artýk int z'nin scopu içerisinde olduðumuz için, aslýnda z'ye kendi deðeri(garbage value) ile atama yapýyoruz.
						// Bundan dolayý da undefined behaviour oluyor.
	// bunu fonksiyon tanýmý olarak düþün
	//	void foo(int foo); -> mesela burada UB yok çünkü parametrenin bulunduðu  scope farklý
	y = 30; // main bloðu içerisindeki y'nin deðerini 30 yapar.
	::y = 12312; // global namespacedeki y'nin deðerini 12312 yapar.
}

void foo(int foo) {
	foo(foo); // buna bakýnca sanki recursive function gibi duruyor FAKAT DEÐÝL! Ýsim arama kurallarýna göre, foo burada fonksiyonun adý mý yoksa parametre deðiþkeninin adý mý?
				// tabiiki de parametre deðiþkeninin adý. Parametre deðiþkenlerinin scope'u fonksiyonun gövdesi içerisinde. Bundan dolayý sentaks hatasý!
					// Ek olarak, parametre ismi block scopeta iken, fonksiyon adý file scopeta.

	::foo(foo); // böyle recursive yapýlabilir. Unary Scope resolution operator kullanýlarak
}

int main(void)
{
	int x = 10;
	if (x > 5) {
		double x; 5.;
		x = 40; // 97. satýrda tanýmladýðýmýz double x, int x'i maskeler. 
					// bu maskeleme iþini engellemek için bir araç yok :/ çünkü ikisi de main bloðu içerisinde,. Unary scope res. ancak global için iþ yapýyor.
	}
}
//hatýrlatma
// source file: preprocessor direktiflerinin yapýlmadýðý olduðu yer.
// Translation unit: Derleyicinin gördüðü kodun çýktýðý yer, preprocessor direktifleri burada yapýlmýþ oluyor.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

													/*						ODR(One Definition Rule)						*/
/*																				Tek tanýmlama Kuralý
	- Varlýklarýn bir proje içerisinde sadece bir kere tanýmlanma haklarý vardýr. Farklý dosyalarda bile olsalar, ayný proje içinde bulunuyorlar ise ODR kuralýný çiðnemiþ oluruz.
	- Her declaration bir definitionn deðildir ama her definition bir declarationdur.
	- Fonksiyon ve global deðiþkenlerin proje dahilinde birden fazla tanýmlamasý OLAMAZ. 

Ýstisna durumlar:
	- inline function
	- inline variables
	- constexpr functions
	- template definitions 
*/


													/*						Inline Functions								*/
/*
Inline expansion: Derleyicinin kullandýðý, en etkili, optimizasyon tekniklerinden biri.
	- Kodu as-if(öyleymiþ gibi) derliyor. Bu sayede koda optimizasyon saðlýyor.
		Öyleymiþ gibi derken aslýnda kodun deðiþtirilmesi olayý var ama observable behaviour deðiþmiyor! Diyelim ki döngü içerisinde, 3 defa, ekrana "hello, world" yazdýran bir program var.
			Derleyici for döngüsü kullanmak yerine döngü olmadan ekrana 3 defa yazdýrarak kaynaklardan tasarruf edebilir. Bunun gibi deðiþiklikler. Daha karmaþýk iþlemler de var tabii.
	
	- Taným görülmek zorunda. Derleyici, kodu gördükten sonra bir analizden geçirir ve duruma baðlý olarak inline expansion optimizasyonunu uygular. 
		Öyle kafasýna göre "aa hadi burada optimizasyon" yapayým demez. Bazý durumlarda inline expansion, less-efficient code üretimine sebep olabilir.

	- Derleyici yapabilirse. Derleyici tanýmý görüp analiz ettikten sonra inline expansion yapýlabilir olduðuna karar verse dahi optimizasyonu yapamayabilir. Bu, derleyiciyi
		kodlayan kiþilerin yeteneklerine baðlý.

	- Inline expansion switch: IDE'lerin "force inline expansion" gibi açýlýp kapatýlabilen özellikleri olabilir. Hoca çok üstünde durmadý öyle bilgi olsun diye verdi. 
 

	Inline function ile inline expansion karýþtýrýldýðý için ilk expansionu gördük ki function ile karýþtýrmayalým.
------------------------------------------------------------------------------------------------------------------------------------------
Inline functions

- Bir fonksiyonun inline anahtar sözcüðü ile tanýmlamasý, inline expansion ile alakalý hiçbir deðiþikliðe sebep olmuyor.
- Birden fazla kaynak dosyasýda inline fonksiyonlar özdeþ olarak tanýmlanýrsa ODR ihlal edilmez. Bütün tokenlarý ayný olmak zorunda!

//	engin.cpp
	inline int sum_square(int a, int b){
		return a * a + b * b;
	}
//	ali.cpp
	inline int sum_square(int a, int b){
		return a * a + b * b;
	}
- Inline fonksiyonu kodu küçük ve fonksiyonlarýn bir çok kez çaðrýldýðý projelerde kullanmak daha mantýklý. Her fonksiyonu inline tanýmlamak iyi bir fikir deðil.
	eðer fonksiyonun içerisinde baþka bir baþlýk/kaynak dosyasýndan alýnan bir deðiþken veya deðiþken sýnýfý kullanýlýyorsa bu ilave baðýmlýlýklara/dezavantajlara yol açabilir.
		inline keywordunu kullanarak bu fonksiyonlara inline expansion yapýlmasýna OLANAK saðlýyor. GARANTÝ deðil.
- Niye inline fonksiyon yapýyoruz? Fonksiyona yapýlan çaðrýlar için derleyiciye inline expansion OLANAÐI kazandýrmak için. Eðer inline keywordünü kullanmasaydýk
	derleyici fonksiyonun tanýmýný göremeyecekti sadece bildirimini görecekti.
	inline int sum_square(int a, int b) -> böyle olunca tanýmýný görüyor
	int sum_square(int a, int b) -> böyle olunca tanýmýný görmüyor(farklý dosyada ise, mesela bir header file içerisinde olabilir)
		eðer bu fonksiyonu ayný þekilde alýp diðer kaynak dosyasýna yapýþtýrsaydýk bu seferde ODR'ý çiðnemiþ olacaktýk.

- Diyelim ki bir baþlýk dosyasýnda bir inline fonksiyon tanýmladýk. Bu fonksiyonu 5 ayrý kaynak dosyasýnda kullanýyoruz. Her bir kaynak dosyasýnda tekrar tekrar compile edilmesindense
	compile edilmiþ fonksiyonun adresi kullanýlýr. BU GARANTÝ
- Eðer derleyici bir fonksiyonun hem declarationunu hem definitionunu görüyor ise, bu fonksiyonlardan birisinin inline olmasý, o fonksiyonun inline fonksiyon olmasý için yeterli.

	inline int foo(int x, int b){
		return x + b;
	}
	int foo(int x, int b){
		return x + b;
	}
	// hepsini tek tek yazmaya üþeniyorum o yüzden kýsaca;
		- inline int, int þeklinde olsa bile inline fonksiyon
		- int, inline int þeklinde olsa bile inline fonksiyon		
		-  inline, inline þeklinde olsa bile inline	fonksiyon


- C++17 standartý ile yeni bir özellik eklendi.
	inline keywordu global deðiþkenlerin tanýmýna da eklendi. Bunlara 'inline variable' denildi.
		Inline functions ile temel iliþkisi ayný.
- Eðer bir deðiþken inline variable olarak tanýmlanýrsa ve birden fazla kaynak dosyasýnda özdeþ olarak yer alýrsa, ODF çiðnenmemiþ oluyor. Ve diðer kaynak dosyalarýnda yer alan
	inline variables ayný deðiþken oluyor.

		#engin.cpp
		inline int x = 10;
		#ali.cpp
		inline int x = 10;
		#nec.cpp
		inline int x = 10;
	x bir inline variable. 3 ayrý kaynak dosyasýnda özdeþ olarak(bütün tokenlarý ayný) tanýmlanmýþ. Bu aslýnda C'deki extern keywordü gibi. Bu tanýmlar
		ayrý kaynak dosyalarýnda olsa bile hepsi ayný deðiþkenden bahsediyor.(adresleri ayný yani) 7 kocalý hürmüz gibi. Kocalarýn hepsi farklý insanlar ama karýlarý ayný(örneðe bak :/ )

inline int& foo(){
	static int x = 10;

	return x;
	// bu fonksiyon aslýnda çakallýk içeriyor. Fonksiyonun geri dönüþ deðerini l value referans yapýyoruz ve fonksiyonun içerisinde static bir deðiþken tanýmlýyoruz.
		// tanýmladýðýmýz bu deðiþkenin referansýný geri döndürüyoruz. Bu sayede her kaynak dosyasýndan eriþilebilen bir deðiþken tanýmlamýþ olduk. inline variable gibi
			// ama inline fonksiyon ve referans semantiðini kullanarak. Bu çakallýðý ekstra bir .h .cpp istemiyor isek yapýyoruz fakat günümüzde buna 'inline variable' sayesinde ihtiyaç yok
	
}

- Inline variables ile header only proje yapma çok kolay hale geldi.
*/
													/*						NUMARALANDIRMA TÜRLERÝ(enum)						*/
/*
- C dilinde enum türü int ile cast ediliyor. CPP'de ise underlying type yani derleyici karar veriyor. 

Istenmeyen durumlar;
- Örtülü dönüþümler:
	Modern CPP öncesi, numaralandýrma türlerinden aritmetik türlere örtülü dönüþüm var iken aritmetik türlerden numaralandýrma türlerine örtülü dönüþüm yoktu.
		Bu yanlýþ koyulmuþ bir kural. 
		enum Color{
			White, Gray, Blue, Black
		};
		enum Pos{
			On, Off
		};
		int main(){
			Color mycolor;
			mycolor = 12; // sentaks hatasý
			mycolor = Off; // sentaks hatasý

			Color mycolor_2 = Blue;
			int x = mycolor_2; // legal ama bu bir ihmal. Necati hoca bunun legal olmamasý gerektiðini söylüyor. CPP'nin gençlik günahlarýndan biriymiþ, allah affetsin diyelim.
				//typecast operatörleri kullanýlarak bu dönüþümlerin yapýlmasý normal. typecast olmadan örtülü dönüþüm ile yapýldýðýnda bir problem ortaya çýktýðýnda
					// problemi bulmanýn zor olduðundan bahsetti hoca.
		}
		1:50
*/



