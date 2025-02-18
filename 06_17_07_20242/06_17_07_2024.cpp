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
	
	1:22
*/

