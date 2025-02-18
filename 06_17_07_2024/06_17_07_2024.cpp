/*
	Bazý yerlerde parantez sentaksýn bir parçasý, bazý yerlerde de öncelik kazandýrmak için kullanýlýyor.

	int main(void){
		int x = 10;

		(x) // burada x'in value categorysi nedir? PR, L value vs deðil. Eðer parantez içerisindeki x'in
				// deðer kategorisi ne ise o dur.
		((((((x)))))) // ayný mantýk. x'in deðer kategorisi lvalue olduðu için bu da lvalue.
		++(((x))), &(((x))) // lvalue olduðu için bunlar mümkün

		auto sz = sizeof(x); // buradaki x'i kapsayan parantez, öncelik parantezi. Eðer bir deðiþkenin
								// adýný yazýyor isek parantez koymadan da yapabiliyorz bunu.
		auto sz2 = sizeof(int); // buradaki ise sentaksýn gerektirdiði parantez. Çünkü, bir veri türünün sizeof deðerini
									// almak istediðimiz zaman sentaks bizden o veri türünü parantez içine almamýzý bekliyor				
	}
	Type-cast operatörlerinde kullanýlan parantezlerde öncelik parantezi deðil sentaksýn gerektirdiði parantezlerdir.
		static_cast<dönüþümün yapýlacaðý tür>(operand)
		const_cast<dönüþümün yapýlacaðý tür>(operand)
		reinterpreter_cast<dönüþümün yapýlacaðý tür>(operand)
		dynamic_cast<dönüþümün yapýlacaðý tür>(operand)
	CPP'deki typecast türlerinin þöyle de bir avantajý var. Diyelim ki kodumuzda bulunan type-cast operatörüyle
		yaptýðýmýz bir iþlemi arayacaðýz. C'de sadece bir adet type conversion olduðu için(implicit ve explicit)
			tek tek yapýlan tüm conversionlara bakmamýz gerekecekti. CPP ile bu operatörleri kontrol etmemiz yeterli.
				const_cast yaptýysak const_cast ile yapýlan dönüþümlere bakabiliriz. Zaman ve hýz kazandýrýyor bu bize

	Standart Conversion: Dil bazý dönüþümleri(implicit type conversion) kendisi yapýyor/izin veriyor. Bu yapýlan dönüþümlere
		standart conversion deniyor. Mesela türler arasýnda olan örtülü dönüþümler buna örnek olabilir.
			int -> double | double -> int vs.
		enum Fruit {Apple, Banana, Pear};
		int main(){
			int i1 = 190;
			int i2 = 7;
				static_cast<double>(i1) / i2; // burada eðer static cast ile double türüne cast etmeseydik
												// bölme iþlemleri iki deðiþkenin de olduðu türde yapýlacaðý için sonuç int türünde olacaktý.
												// static_cast ile i1'i double türüne cast ettiðimiz için, örtülü dönüþüm ile i2'de double türüne implicit olarak
													// dönüþtürülecek.
			double dval = 3.564;
			int ival = dval; // böyle cast etmek legal fakat doðru deðil. Double türünden bir veriyi int türüne atadýðýmýz için
								// veri kaybý var. Derleyici diagnostic verir fakat kodu derler. Bu iþlemi bilerek, kasten yaptýysak
									// tür dönüþümü operatörü kullnarak bunu belirtmeliyiz. Hem okuyan hem de derleyici için. Bu arada burada yapýlan atama iþlemi 'copy init'
			// int ival = static_cast<int>(dval);
			-------------------------------------------------------------------
			Fruit f = Apple;
			int ival = 3;
			ival = f; // bu maalesef legal. Legality is not morality. Böyle bir yapacaksak bile explicit olarak yapmalýyýz
			ival = static_type<int>(f); // þeklinde yazmalýyýz
			// legal olmayan(CPP implicit olarak desteklemiyor bunu, sentaks hatasý), aritmetik türlerden enum türüne dönüþüm yaparken de bunu kullanmalýyýz.

			f = static_type<Fruit>(ival);
			-------------------------------------------------------------------
			int x{}; // burada value init ile 0 deðerini almasýný saðlýyoruz. int x{10} olsa idi bu uniform/brace init
			void* vp{ &x }; // diðer adres türlerinden void* türüne örtülü dönüþüm var.
			int* ip = vp; // sentaks hatasý çünkü örtülü dönüþüm yok burada.
			int* ip = static_cast<int*>(vp);
		}

		Standart conversionlar için static_cast
		Ýleri de Türemiþ sýnýftan taban sýnýfa(veya tam tersi) compile timeda legalite sýnamak için static_cast kullanýlacak.
		-------------------------------------------------------------------
		enum struct Fruit {Apple, Banana, Pear, Cherry};
		const char* const fnames[] = {"Apple", "Banana", "Pear", "Cherry"};
		int main(){
			Fruit f{fruit::Banana};
			fnames[f]; // burada da bir dönüþüm var. Eðer burada traditional enum kullanýlsaydý(scope'u olmayan enum)
						// sentaks hatasý olmayacaktý burada.
			fnames[static_cast<int>(f)]; // þimdi legal
		
		}

*/

													/*						CONST CAST						*/	
/*
	- Const cast pointer semantiði ile kullanýlabilir. Daha çokta bu konuda karþýmýza çýkacak zaten
	- Genel kullaným amacý const nesne adresindenconst olmayan nesne adresine önüþüm yapýlmasýný saðlayacak
		örneðin const int* -> int* | const int& -> int&
		int main(){
			int x{}; // value init
			const int* cptr = &x; 
			int* iptr;
			iptr = cptr; // bu sentaks hatasý.
			iptry = const_cast<int*>(cptr); // bu þekilde cast etmemiz gerek
			---------------------------------------------------------
			const int& cr = x;
			const_cast<int&>(cr); // referans semantiði için de bu þekilde.
		}
	- Eðer ortada bir adres semantiði yok ise const_cast kullanýlamaz.
		int main(){
			int x{123};
			const_cast<int>(x); // böyle bir þey YOK! legal deðil bu		
		}
	- const_cast'ý kullanýrken dikkat etmek gerekiyor. Fiziksel olarak const olan bir nesnenin adresini const deðilmiþ
		gibi kullanmak çok sýkýntýlý bir durum. 
		Contractual Constness ve Physical Constness
		int main(){
			int x{456};
			const int* p1 = &x;
			*p; // p1'in gösterdiði nesne const olmasa da p1 nesnesinin const olmasý sebebiyle const gibi iþlem oluyor.
					// buna da contractual constness deniyor.
			int* ptr = const_cast<int*>(p1); // sentaks hatasý yok, const hatasý da yok çünkü p1 nesnesi x'i gösteriyor ve x const deðil.
			
			const int z{123};
			const int* p2 = &z; 
			*p2; // *p2 artýk sadece contractual const deðil ayný zamanda physical const.
			int* ptr2 = const_cast<int*>(p2); // bu yanlýþ, const bir nesnenin constluðunu almaya çalýþýyoruz.
				// çünkü z physical const.

		}
	- Dilin kurallarý, const olmayan nesne adresi türünden const nesne adresi türüne de const_cast'in kullanýlmasýna izin veriyor.
		genellikle generic kodlamalarda çýkar karþýmýza.
		int main(){
			int x{ 123 };
			auto p = const_cast<const int*>(&x); // burada type-deduction ile p'nin türü const int* olacak. -> auto için
			// bu dönüþüm örtülü olarak yapýlýyor zaten. Çok ender karþýmýza çýkar (generic kodlamalarda belki)

			const int* p = &x; // burada zaten implicit type conversion var.
			
		}
		
		
*/
												/*						reinterpret_cast						*/	
/*
	- reinterpret_cast gördüklerimize göre daha riskli. Çok daha dikkatli kullanmalýyýz
	Kullaným Amacý:
		- Bir nesne adresini farklý türden bir nesne adresiymiþ gibi kullanmak
		- Tam sayý deðerlerini adres deðerleri olarak kullanmak
	
	- Bazý durumlarda nesneleri byte byte incelemek için signed char, unsigned char(char* dahil) türlerinde kullanabiliyoruz.
		int main(){

			int x{43124};
			char* cp = &x; // legal deðil. Türler farklý
			char* cp = (char*)&x; // c-style explicit conversion bu þekilde fakat biz CPP'ye uygun yapýcaz.
			char* cp = reinterpret_cast<char*>(&x); 
 		}
	- Bir tam sayý deðerini adres deðeri olarak kullanmak
	int main(){
			int* p = 0x1AC4; // Atama operatörünün saðýnda kalan ifade int türünden bir tam sayý. Bundan dolayý sentaks hatasý.
			int* p = reinterpret_cast<int*>(0x1AC4);  // legal
		}
	- Const bir nesnenin adresi, const olmayan bir nesnenin adresini tutan deðiþkene dönüþtürülmesi sentaks hatasý.
		int main(){
			const int x = 56;
			reinterpret_cast<char *>(&x); // sentaks hatasý. const olan bir nesneden const olmayan bir nesneye dönüþtürülüyor.
			const_cast<char*>(reinterpret_cast<const char*>(&x)); // bu legal.
			reinterpret_cast<char*>(const_cast<int *>(&x)); // bu da legal

			const char* cp = &x; // örtülü dönüþüm yok bunu da unutma
		}
		En iyisi explicit dönüþüm, hiç yapýlmamýþ olan dönüþümdür.
	--------------------------------------------------------------
	- CPP'de eskiden beri gelen 'functional explicit type cast' diye bir þey var.
		Normalde biz örtüsüz tür dönüþümü yaparken '(hedef tür)deðiþken adý' þeklinde yapýyorduk. CPP'de ise bir þekil daha var.
			'hedef tür(deðiþken adý)' þeklinde. dval(x) gibi. Functional type cast'in garip bir özelliði var.

		int main(){
			double dval = 5.;
			(unsigned int)dval; // C ve CPP'de legal.
			static_cast<unsigned int>(dval); // legal.
			auto x = unsigned int(dval); //  sýkýntý yok
			auto x = long int(dval); //  birden fazla anahtar sözcük var ise sentaks hatasý veriyor.
		}
*/

												/*						constexpr						*/	

/*
	- constexpr modern CPP(C++11) ile eklenmiþ bir keyword. 
	- Constant expressiondan uydurulmuþ bir kelime olsa da direkt olarakconst expression ile iliþkilendirmeyelim
	- constexpr bir specifier bir type qualifier deðil. 
		constexpr ile tanýmlananlar hem sabit olmak zorunda hem de deðiþtirilemez.
			constexpr ise bir sabit ifadesi olduðunu belirtiyor. 5 bir sabit mesela.
		const ile tanýmlananlar deðiþtirelemez fakat deðeri sabit olabilir ya da olmayabilir
			const keywordü bir nesnenin deðiþtirilemez olduðunu, deðerinin compile timeda belli olduðunu belirtir.
	
	const int x = 10;

	X ifadesi C'de sabit ifadesi gerektiren yerlerde kullanýlamýyor. 
		Bir dizinin boyutunu belirtmek için kullanýlamaz. -> int a[x]; bu ifade deyimi yanlýþ.
		Global namespacedeki bir deðiþken sabit bir ifade ile baþlatýlmak zorunda. int a = x; bu yanlýþ. int a = 10; doðru
		switch deyimindeki kontrolü saðlayan ifade sabit ifade olmak zorunda.
		Bitsel iþlemlerdeki bit size sabit olmalý. Designated int gibi ifadeler kullanýlýyor.

	C++ta ise ifadeye göre deðiþiyor
		const int x = 10; saðdaki ifade sabit ise bu sabit gereken yerlerde kullanýlabilir.
		int foo();
		const int x = foo(); legal-geçerli, constexpr kullanýlýr ise foo() sabit ifadesi olmadýðý için kullanýlamaz.
		
		const bir nesneye sabit ifadesi ile ilk deðer verirsek, sabit ifade gereken yerlerde kullanabiliriz.

	constexpr int x = 45; // bu deyimin decltype'ý const int. constexpr bir tür deðil, bir specifier.
	- constexpr her türde kullanýlamýyabilir. Kullanýlan türün 'literal type' denilen bir tür kategorisine
		iliþkin olmasý gerek. Bu konuyu ileride görücez.
	- constexpr, sabit ifadesinin gerektiði yerlerde kullanýlabileceðinin GARANTÝSÝNÝ veriyor. const'ta böyle bir garanti yok.
	

	const int a = 10;
	const int b = 30;
	int c = 20;
	constexpr auto d = a + b; // legal, bir sýkýntý yok. Her iki ifade de bir sabit

	constexpr auto e = a + c; // a sabit bir ifade fakat c const deðil bundan dolayý sabit ifade de deðil. Sentaks hatasý
	
	

	ÖNEMLÝ!! bu çok karýþtýrýlýyor
	constexpr pointerlarda high const olarak yani const pointer to int olarak iþ görüyor.
	int* const p = &x; gibi düþünebiliriz. Constexpr ifadeyi hem deðiþtirilemez hem de sabit olmasý gerektiðini niteliyor.

	int x = 10;
	int y = 20;

	int main(){
		constexpr int* p = &x; // bu legal, çünkü x'in adresi bir sabit ve o adres deðiþtirilemez.
		p = &y; // bu illegal, çünkü constexpr high-const olarak görev yapýyor burada. p deðiþkenini niteliyor.
		*p = 5; // legal, x'in deðeri 5 yapýlacak. low const olsaydý deðiþtirilemezdi.
		constexpr const int* ptr = &y; // bu low ve high const. Yani ne ptr deðiþkeni ne de onun gösterdiði nesnenin
											// içeriði üzerinde deðiþiklik yapýlamaz.
		ptr = &x; // illegal
		*ptr = 1; // illegai
	}

	referanslarda constexpr kullanýlabilir, bir sýkýntý yok ama redundant. Zaten referans semantiði ile
		tanýmlanmýþ deðiþkenler const reference to data_type oluyor. high const gibi olacaðý için
			constexpr redundant yani gereksiz.

	constexpr ile dizi de tanýmlanabilir

	constexpr int a[] = {3, 7, 8, 1, 9, 6};
	constexpr auto i1 = a[2]; // sentaks hatasý yok çünkü i1'e ilk deðeri veren ifade de constexpr(sabit ifade)
		olduðu için sentaks hatasý yok. Lookup tablelarý, elemanlarýnýnda const expr olmasýni istersek
			constexpr ile tanýmlayabiliriz.

////////////////////////////////////////////////////////////////////////

	FONKSIYONLARDA CONSTEXPR KULLANIMI

	CPP diline ilk eklendiðinde çok fazla kýsýtlamalar vardý sonradan gelen standartlar ile beraber
		bu kýsýtlamalar baya azaldý. Þu anda olan kýsýtlamalardan örnek:
		- Fonksiyonun geri dönüþ deðer, parametre deðiþkenleri veya fonksiyonun içerisinde tanýmlanan
			deðiþkenlerinin literal type(sabit tür) olmasý durumunda return edilen deðeri compile timeda elde ediliyor. 
		- constexpr fonksiyonun içerisinde statik ömürlü deðiþken tanýmlanamýyor.
	

	garanti: parametreler const expr, geri dönüþ deðeri derleme zamanýnda constexpr gereken bir yerde kullanýlýrsa

	Eðer parametreler const expression, geri dönüþ deðeri constexpr gereken yerde kullanýlýyor ise
		ifadenin deðeri derleme zamanýnda belli olur. Bu GARANTÝ altýnda. Yani kesinlikle yapýlacak bu optimizasyon
			eðer kriterler ok ise

	constexpr int func(int x){
		return x * x + 5;
	}
	int main(){
		int x = func(23); // burada x constexpr deðil deðeri runtimeda belli olacak
		constexpr int y = func(2) + func(3); // y constexpr bir ifade, func'a gönderilen parametreler const expression
												// y'nin deðeri compile timeda belli olacak
		const int z = func(2) + func(3); // burada da optimizasyon yapýlacan ve z'nin deðeri compile timeda belli olacak
	}
	Þu an için bu çokta önemli gibi durmasa da, generic programlamada sabit ifadelerin kullanýmý oldukça fazla.
		Bu optimizasyon orada baya bir önem kazanacak.

	constexpr fonksiyonlar implicitly inline. constexpr fonksiyonun tanýmýný baþlýk dosyasýna koyabiliyoruz.
		implicit inline olduðu için ODR'da çiðnenmiyor.

// prime.h
constexpr bool is_prime(int x){
	if(x < 2)
		return false;
	if(x % 2 == 0) return x == 2;
	if(x % 3 == 0) return x == 3;
	if(x % 5 == 0) return x == 5;

	for(int i = 7; i <= x; i += 2){
		if(x % i == 0)
			return false;
	}
	return true;
}

	Bir fonksiyonun constexpr olmasý o fonksiyonun sadece compile timeda kullanýlabileceði
		diðer deðiþkenler tarafýndan runtimeda çaðrýlamayacaðý anlamýna GELMÝYOR. Belirli kriterler karþýlandýðýnda
			compile timeda deðer döndürüyor. Eðer o kriterler yok ise runtimeda çalýþýyor.
int main(){
	constexpr auto x = 19871;
	constexpr auto y = 18;
	constexpr auto b = is_prime(x + y); // fonksiyona gönderilen ifade const expression geri dönüþ deðeri compile time

	auto t = 10;
	auto bprime = is_prime(t); // runtimeda belli olacak
	constexpr auto cbprime = is_prime(t); // sentaks hatasý çünkü parametre bir sabit ifade deðil. Eðer t constexpr auto t = 10 olsaydý
											// sentaks hatasý olmayacaktý.

}
	Eðer bir Undefined Behaviour durumu var ise ve constexpr fonksiyonu constant expression gereken yerde
		constant expression parametreleri aldýysa Undefined Behaviour da ayný þekilde derleme zamanýnda oluþacaðý için
			derleyici bu durum için bir diagnostic veriyor.

	Bazý deðerlerin compile timeda hesaplanmasý verimi arttýrýyor.

	Eðer derleyici bildirimi ve tanýmý ayný anda görürse ikisinde de constexpr olmak zorunda.
		inline fonksiyonlar için birisinde olmasý yetiyordu. constexpr için bu geçerli deðil
		Ýkisi de constexpr deðil ise sentaks hatasý. const içind geçerli bu durum

//main.cpp veya header.h
	bool is_prime(int);

	constexpr bool is_prime(int x){
		if(x < 2)
			return false;
		if(x % 2 == 0) return x == 2;
		if(x % 3 == 0) return x == 3;
		if(x % 5 == 0) return x == 5;

		for(int i = 7; i <= x; i += 2){
			if(x % i == 0)
				return false;
		}
		return true;
	}


*/
/*
	C dilinde sayýlar 3 farklý sistemde yazýlabilir.
		-octal -> 0123 (0 ön eki ile)
		-decimal -> 454 
		-hexadecimal -> 0xA123 (0x ön eki ile)
	C dili ikili sistemde(binary) sabit sayýlarýn yazýmýný standart olarka desteklemiyor. Compilerýn extensionlarý
		bunu yazmayý mümkün kýlabilir.
	CPP'de modern cpp ile beraber bu mümkün oldu.
		-binary -> 0b1001 (0b ön eki ile)
	Kullanýlan ön eklerdeki harfler büyük veya küçük olabilir. Case insensitivity yok yani(0b -> 0B, 0x -> 0X)
	Sabit sayýlar için kullanýlan bu sistemler sadece sayýnýn yazýlýþ þeklini deðiþtiriyor.
		Sabit sayýnýn tutulduðu deðiþkenin türü(auto kullanýldýðýný varsayarak) sayýnýn büyüklüðü veya sonda
			bulunan suffixlere göre belirleniyor.

	auto x1 = 44; // x1 int türünden
	auto x2 = 44u; // x2 unsigned int türünden
	auto x3 = 44ul; // x3 unsigned long türünden
	auto x4 = 0b10111111ull; // x4 unsigned long long türünden

	CPP'de digit seperator(C de compiler extension olarak var) standart olan bir araç var. Sayýlarý ayýrmak
		için kullanýlýyor.
	100'000'000 -> bu single quote karakterleri görsel ayýraç olarak kullanýlýyor.

	auto x = 1082362138880312; // çok karýþýk mesela bu
	auto x = 1'082'362'138'880'312; // okumasý daha kolay oldu
		Bu sayýnýn türünü vs hiçbir þeyini deðiþtirmiyor. Sadece yazma ve okuma kolaylýðý saðlýyor.
*/
/*
	attribute(öznitelik) -> modern cpp ile geldi standart
	Kendine ait bir sentaksý var.
	[[nodiscard]] -> iki köþeli parantez içine yazýlýyor. Ne iþe yarýyor peki attribute?

	attributelarýn ne olduklarýna baðlý olarka, 
	-Derleyiciyi uyarý mesajý vermeye teþvik ediyor.
	-Derleyiciyi uyarý vermemeye teþvik ediyor(sanýrým bu _CRT_SECURE_NO_WARNINGS makrosu gibi)
	-Bazýlarý derleyiciye kodla ilgili bilgi verip derleyicinin daha iyi optimizasyon yapmasýný saðlýyor.

	Özetle: Kullanýlan attribute'a baðlý olarak belirli iþlemler hakkýnda yardýmcý oluyor/bilgi veriyor.(ileride görülecek)
	attribute konusu ileride detaylý olarak görülecek ama nodiscard için görsle bir örnek:
	Bazý fonksiyonlarýn amacý döndürdükleri deðer. fonksiyon içinde yapýlan hiçbir iþlem dýþarýsý için önemli deðil.
		Bunlara pure functions deniyor.

	#include <iostream> // printf'i alýcaz burada
	bool is_prime(int x); 
	
	[[nodiscard]] is_prime_nodiscard(int x); // önce aþaðýyý oku sonra buna bak

	int main(){
		printf("attribute"); // printf fonksiyonun geri dönüþ deðeri standart outputa gönderdiði karakter sayýsý
								// geri dönüþü önemli deðil o yüzden discard(ýskartaya çýkarmak) edilebilir.
		int x = 10;
		is_prime(x); // bu fonksiyonun tek amacý kendisine gönderilen sayýnýn prime olup olmadýðý bilgisini vermek.
						// biz bunun geri dönüþ deðerini kullanmazsak bu fonksiyonun bir amacý kalmýyor. derleyici de hata vermez.
		// Eðer warning vermesini istiyor isek fonksiyonu [[nodiscard]] attribute'u ile nitelemeliyiz. Bu attribute
			// fonksiyonun geri dönüþ deðerinin kullanýlmamasý durumunda derleyici tarafýndan diagnostic vermesini saðlýyor.
				// program halen derlenir ama warning mesajýmýz olur. Error vermiyor yani çalýþmasýn da sýkýntý olmaz
				// problemin nerede olduðunu görmek için çok iyi.
		int y = 20;
		is_prime_nodiscard(y); // derleyici warning mesajý verecek
	}
*/








														/*						Function Overloading						*/
/*
C dilinde external linkage ait, global isim alanýnda ayný isimde fonksiyonlar tanýmlanamýyor.
CPP de function overloading sayesinde BELÝRLÝ KOÞULLAR ALTINDA ayný isme sahip, farklý kodlara sahip olmasýna raðmen
	mümkün kýlýyor. 
	
Function overloading yüksek düzeyde bir ortak soyutlama saðlýyor. Yazýlýmcýnýn da iþini kolaylaþtýrýyor bu durum
C dilinde f. overloading olmadýðý için ayný iþlemi farklý türler için yapan fonksiyonlarýn adlarý farklý
	Bu da kafa karýþýklýðýna yol açabiliyor.
	abs -> int için mutlak deðer
	fabs -> float için
	labs -> long için
	yani her tür için ismi farklý fonksiyonlar yazýlmasý gerek. 
CPP de direkt olarak ayný isme sahip ama farklý amaçlara hizmet edebilen fonksiyonlar yazabiliyoruz. Bu da okuyan/öðrenen kiþi
	açýsýndan kolaylýk saðlýyor.
	abs -> tüm türler için bu ismi kullanýyoruz

Bir fonksiyona çaðrý yaptýðýmýzda ifadenin türü ile ilgili fonksiyona karar verilirken
	Derleyicinin bu kararý vermek/iþi yapmak için gerçekleþen bu sürece "Function Overload Resolution" deniyor.

bind:
	static binding(early binding) : hangi fonksiyona baðlanacaðý derleme zamanýnda belli oluyor ise
	dynamic binding(late binding) : hangi fonksiyona baðlanacaðý derleyici tarafýndan anlaþýlmýyor
										çalýþma zamanýnda belli oluyor ise

	Function overloading compile timeda belli oluyor yani static binding.


Function overloading resolution ile function overloading var mý yok mu? sürecini karýþtýrmamak gerekiyor.
	Çoðu kiþi bu iki durumu karýþtýrdýðý için problem yaþýyor DÝKKAT!

Function Overloading Kullanmak için
- Fonksiyonlarýn ismi ayný olacak
- Scopelarý ayný olacak(ayný deðilse name masking ihtimali var)
- Signaturelarý(imza) farklý olacak. Geri dönüþ deðeri türü söz konusu olmadan parametrik yapýnýn geri kalan kýsmý
	fonksiyonun imzasý oluyor.
	int foo(int, int) -> bunun imzasý ilk ve ikinci parametresinin int olmasý
	double foo(double, double) -> bunun da double double olmasý
	long foo(long, int) -> long - int þeklinde gidiyor.
	Geri dönüþ deðerlerinin hangi türden olduðu önemli deðil

BUNA DÝKKAT ETMEK GEREKÝYOR
	Ortada bir function overloading yok ise ve ayný isme sahip iki veya daha fazla fonksiyon var ise 2 durum söz konusu olabilir;
	1- sentaks hatasý, çünkü bir fonksiyonun tekrar tanýmlanmasý sentaks hatasý
	2- redeclaration (ki bu function overloading ile çok karýþtýrýlýyor)
		int foo(int);
		int foo(int); 
		redeclaration için hem imzalarýnýn hem de geri dönüþ deðerlerinin ayný olmasý gerek.
		int bar(int);
		void bar(int); bu artýk redeclaration deðil sentaks hatasý çünkü geri dönüþ deðeri farklý.
		
-const keyword imza farklýlýðý yapmýyor(low-level const pointer hariç)
	void bar(int);
	void bar(const int); Bu bir redeclaration çünkü const imza farklýlýðý oluþturmuyor. Redeclaration

	void baz(int* p);
	void baz(int* const p); Buradaki const p deðiþkenini const yaptýðý için gene imza farklýlýðý oluþturmuyor. Redeclaration

	void foo(int* p);
	void foo(const int* p); Burada const gelen deðiþkeni const(contractual) yaptýðý için artýk farklý bir tür. Func overloading
		
-Parametrelerin char, unsigned char ve signed char'a olmasý imza farklýlýðý oluþturur.
	void foo(char);
	void foo(signed char);
	void foo(unsigned char);
	Yukarýda 3 adet overloaded function var. 
-Fonksiyon parametre deðiþkeni olarak kullanýlan typedefler imza farklýlýðý oluþturmuyor.
	typedef int Word
	void bar(int);
	void bar(Word); Bu bir redeclaration
	FAKAT!
	#include <stdint>
	void baz(int32_t);
	void baz(int);
	Yukarýdaki bu örnek int32_t bir tür eþ ismi olsa da derleyicinin int32_t'nin hangi türün tür eþ ismi olduðuna
		baðlý olarak, redeclaration veya func overloading olabilir. Eðer int32_t int türünün tür eþ ismi ise redeclaration
			baþka bir tür ise func overloading. (int32_t tür eþ ismini dile eklemek derleyicinin kararýna baðlý, opsiyonel)


*/



/*
	Dilde bir aracý öðrenirken þu sorularý sor
1) Ne iþe yarýyor?
2) Compile time / run time nerede çalýþýyor (mülakatlarda sorabiliyorlar bunu)
*/

