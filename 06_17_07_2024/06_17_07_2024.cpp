/*
	Baz� yerlerde parantez sentaks�n bir par�as�, baz� yerlerde de �ncelik kazand�rmak i�in kullan�l�yor.

	int main(void){
		int x = 10;

		(x) // burada x'in value categorysi nedir? PR, L value vs de�il. E�er parantez i�erisindeki x'in
				// de�er kategorisi ne ise o dur.
		((((((x)))))) // ayn� mant�k. x'in de�er kategorisi lvalue oldu�u i�in bu da lvalue.
		++(((x))), &(((x))) // lvalue oldu�u i�in bunlar m�mk�n

		auto sz = sizeof(x); // buradaki x'i kapsayan parantez, �ncelik parantezi. E�er bir de�i�kenin
								// ad�n� yaz�yor isek parantez koymadan da yapabiliyorz bunu.
		auto sz2 = sizeof(int); // buradaki ise sentaks�n gerektirdi�i parantez. ��nk�, bir veri t�r�n�n sizeof de�erini
									// almak istedi�imiz zaman sentaks bizden o veri t�r�n� parantez i�ine almam�z� bekliyor				
	}
	Type-cast operat�rlerinde kullan�lan parantezlerde �ncelik parantezi de�il sentaks�n gerektirdi�i parantezlerdir.
		static_cast<d�n���m�n yap�laca�� t�r>(operand)
		const_cast<d�n���m�n yap�laca�� t�r>(operand)
		reinterpreter_cast<d�n���m�n yap�laca�� t�r>(operand)
		dynamic_cast<d�n���m�n yap�laca�� t�r>(operand)
	CPP'deki typecast t�rlerinin ��yle de bir avantaj� var. Diyelim ki kodumuzda bulunan type-cast operat�r�yle
		yapt���m�z bir i�lemi arayaca��z. C'de sadece bir adet type conversion oldu�u i�in(implicit ve explicit)
			tek tek yap�lan t�m conversionlara bakmam�z gerekecekti. CPP ile bu operat�rleri kontrol etmemiz yeterli.
				const_cast yapt�ysak const_cast ile yap�lan d�n���mlere bakabiliriz. Zaman ve h�z kazand�r�yor bu bize

	Standart Conversion: Dil baz� d�n���mleri(implicit type conversion) kendisi yap�yor/izin veriyor. Bu yap�lan d�n���mlere
		standart conversion deniyor. Mesela t�rler aras�nda olan �rt�l� d�n���mler buna �rnek olabilir.
			int -> double | double -> int vs.
		enum Fruit {Apple, Banana, Pear};
		int main(){
			int i1 = 190;
			int i2 = 7;
				static_cast<double>(i1) / i2; // burada e�er static cast ile double t�r�ne cast etmeseydik
												// b�lme i�lemleri iki de�i�kenin de oldu�u t�rde yap�laca�� i�in sonu� int t�r�nde olacakt�.
												// static_cast ile i1'i double t�r�ne cast etti�imiz i�in, �rt�l� d�n���m ile i2'de double t�r�ne implicit olarak
													// d�n��t�r�lecek.
			double dval = 3.564;
			int ival = dval; // b�yle cast etmek legal fakat do�ru de�il. Double t�r�nden bir veriyi int t�r�ne atad���m�z i�in
								// veri kayb� var. Derleyici diagnostic verir fakat kodu derler. Bu i�lemi bilerek, kasten yapt�ysak
									// t�r d�n���m� operat�r� kullnarak bunu belirtmeliyiz. Hem okuyan hem de derleyici i�in. Bu arada burada yap�lan atama i�lemi 'copy init'
			// int ival = static_cast<int>(dval);
			-------------------------------------------------------------------
			Fruit f = Apple;
			int ival = 3;
			ival = f; // bu maalesef legal. Legality is not morality. B�yle bir yapacaksak bile explicit olarak yapmal�y�z
			ival = static_type<int>(f); // �eklinde yazmal�y�z
			// legal olmayan(CPP implicit olarak desteklemiyor bunu, sentaks hatas�), aritmetik t�rlerden enum t�r�ne d�n���m yaparken de bunu kullanmal�y�z.

			f = static_type<Fruit>(ival);
			-------------------------------------------------------------------
			int x{}; // burada value init ile 0 de�erini almas�n� sa�l�yoruz. int x{10} olsa idi bu uniform/brace init
			void* vp{ &x }; // di�er adres t�rlerinden void* t�r�ne �rt�l� d�n���m var.
			int* ip = vp; // sentaks hatas� ��nk� �rt�l� d�n���m yok burada.
			int* ip = static_cast<int*>(vp);
		}

		Standart conversionlar i�in static_cast
		�leri de T�remi� s�n�ftan taban s�n�fa(veya tam tersi) compile timeda legalite s�namak i�in static_cast kullan�lacak.
		-------------------------------------------------------------------
		enum struct Fruit {Apple, Banana, Pear, Cherry};
		const char* const fnames[] = {"Apple", "Banana", "Pear", "Cherry"};
		int main(){
			Fruit f{fruit::Banana};
			fnames[f]; // burada da bir d�n���m var. E�er burada traditional enum kullan�lsayd�(scope'u olmayan enum)
						// sentaks hatas� olmayacakt� burada.
			fnames[static_cast<int>(f)]; // �imdi legal
		
		}

*/

													/*						CONST CAST						*/	
/*
	- Const cast pointer semanti�i ile kullan�labilir. Daha �okta bu konuda kar��m�za ��kacak zaten
	- Genel kullan�m amac� const nesne adresindenconst olmayan nesne adresine �n���m yap�lmas�n� sa�layacak
		�rne�in const int* -> int* | const int& -> int&
		int main(){
			int x{}; // value init
			const int* cptr = &x; 
			int* iptr;
			iptr = cptr; // bu sentaks hatas�.
			iptry = const_cast<int*>(cptr); // bu �ekilde cast etmemiz gerek
			---------------------------------------------------------
			const int& cr = x;
			const_cast<int&>(cr); // referans semanti�i i�in de bu �ekilde.
		}
	- E�er ortada bir adres semanti�i yok ise const_cast kullan�lamaz.
		int main(){
			int x{123};
			const_cast<int>(x); // b�yle bir �ey YOK! legal de�il bu		
		}
	- const_cast'� kullan�rken dikkat etmek gerekiyor. Fiziksel olarak const olan bir nesnenin adresini const de�ilmi�
		gibi kullanmak �ok s�k�nt�l� bir durum. 
		Contractual Constness ve Physical Constness
		int main(){
			int x{456};
			const int* p1 = &x;
			*p; // p1'in g�sterdi�i nesne const olmasa da p1 nesnesinin const olmas� sebebiyle const gibi i�lem oluyor.
					// buna da contractual constness deniyor.
			int* ptr = const_cast<int*>(p1); // sentaks hatas� yok, const hatas� da yok ��nk� p1 nesnesi x'i g�steriyor ve x const de�il.
			
			const int z{123};
			const int* p2 = &z; 
			*p2; // *p2 art�k sadece contractual const de�il ayn� zamanda physical const.
			int* ptr2 = const_cast<int*>(p2); // bu yanl��, const bir nesnenin constlu�unu almaya �al���yoruz.
				// ��nk� z physical const.

		}
	- Dilin kurallar�, const olmayan nesne adresi t�r�nden const nesne adresi t�r�ne de const_cast'in kullan�lmas�na izin veriyor.
		genellikle generic kodlamalarda ��kar kar��m�za.
		int main(){
			int x{ 123 };
			auto p = const_cast<const int*>(&x); // burada type-deduction ile p'nin t�r� const int* olacak. -> auto i�in
			// bu d�n���m �rt�l� olarak yap�l�yor zaten. �ok ender kar��m�za ��kar (generic kodlamalarda belki)

			const int* p = &x; // burada zaten implicit type conversion var.
			
		}
		
		
*/
												/*						reinterpret_cast						*/	
/*
	- reinterpret_cast g�rd�klerimize g�re daha riskli. �ok daha dikkatli kullanmal�y�z
	Kullan�m Amac�:
		- Bir nesne adresini farkl� t�rden bir nesne adresiymi� gibi kullanmak
		- Tam say� de�erlerini adres de�erleri olarak kullanmak
	
	- Baz� durumlarda nesneleri byte byte incelemek i�in signed char, unsigned char(char* dahil) t�rlerinde kullanabiliyoruz.
		int main(){

			int x{43124};
			char* cp = &x; // legal de�il. T�rler farkl�
			char* cp = (char*)&x; // c-style explicit conversion bu �ekilde fakat biz CPP'ye uygun yap�caz.
			char* cp = reinterpret_cast<char*>(&x); 
 		}
	- Bir tam say� de�erini adres de�eri olarak kullanmak
	int main(){
			int* p = 0x1AC4; // Atama operat�r�n�n sa��nda kalan ifade int t�r�nden bir tam say�. Bundan dolay� sentaks hatas�.
			int* p = reinterpret_cast<int*>(0x1AC4);  // legal
		}
	- Const bir nesnenin adresi, const olmayan bir nesnenin adresini tutan de�i�kene d�n��t�r�lmesi sentaks hatas�.
		int main(){
			const int x = 56;
			reinterpret_cast<char *>(&x); // sentaks hatas�. const olan bir nesneden const olmayan bir nesneye d�n��t�r�l�yor.
			const_cast<char*>(reinterpret_cast<const char*>(&x)); // bu legal.
			reinterpret_cast<char*>(const_cast<int *>(&x)); // bu da legal

			const char* cp = &x; // �rt�l� d�n���m yok bunu da unutma
		}
		En iyisi explicit d�n���m, hi� yap�lmam�� olan d�n���md�r.
	--------------------------------------------------------------
	- CPP'de eskiden beri gelen 'functional explicit type cast' diye bir �ey var.
		Normalde biz �rt�s�z t�r d�n���m� yaparken '(hedef t�r)de�i�ken ad�' �eklinde yap�yorduk. CPP'de ise bir �ekil daha var.
			'hedef t�r(de�i�ken ad�)' �eklinde. dval(x) gibi. Functional type cast'in garip bir �zelli�i var.

		int main(){
			double dval = 5.;
			(unsigned int)dval; // C ve CPP'de legal.
			static_cast<unsigned int>(dval); // legal.
			auto x = unsigned int(dval); //  s�k�nt� yok
			auto x = long int(dval); //  birden fazla anahtar s�zc�k var ise sentaks hatas� veriyor.
		}
*/

												/*						constexpr						*/	

/*
	- constexpr modern CPP(C++11) ile eklenmi� bir keyword. 
	- Constant expressiondan uydurulmu� bir kelime olsa da direkt olarakconst expression ile ili�kilendirmeyelim
	- constexpr bir specifier bir type qualifier de�il. 
		constexpr ile tan�mlananlar hem sabit olmak zorunda hem de de�i�tirilemez.
			constexpr ise bir sabit ifadesi oldu�unu belirtiyor. 5 bir sabit mesela.
		const ile tan�mlananlar de�i�tirelemez fakat de�eri sabit olabilir ya da olmayabilir
			const keyword� bir nesnenin de�i�tirilemez oldu�unu, de�erinin compile timeda belli oldu�unu belirtir.
	
	const int x = 10;

	X ifadesi C'de sabit ifadesi gerektiren yerlerde kullan�lam�yor. 
		Bir dizinin boyutunu belirtmek i�in kullan�lamaz. -> int a[x]; bu ifade deyimi yanl��.
		Global namespacedeki bir de�i�ken sabit bir ifade ile ba�lat�lmak zorunda. int a = x; bu yanl��. int a = 10; do�ru
		switch deyimindeki kontrol� sa�layan ifade sabit ifade olmak zorunda.
		Bitsel i�lemlerdeki bit size sabit olmal�. Designated int gibi ifadeler kullan�l�yor.

	C++ta ise ifadeye g�re de�i�iyor
		const int x = 10; sa�daki ifade sabit ise bu sabit gereken yerlerde kullan�labilir.
		int foo();
		const int x = foo(); legal-ge�erli, constexpr kullan�l�r ise foo() sabit ifadesi olmad��� i�in kullan�lamaz.
		
		const bir nesneye sabit ifadesi ile ilk de�er verirsek, sabit ifade gereken yerlerde kullanabiliriz.

	constexpr int x = 45; // bu deyimin decltype'� const int. constexpr bir t�r de�il, bir specifier.
	- constexpr her t�rde kullan�lam�yabilir. Kullan�lan t�r�n 'literal type' denilen bir t�r kategorisine
		ili�kin olmas� gerek. Bu konuyu ileride g�r�cez.
	- constexpr, sabit ifadesinin gerekti�i yerlerde kullan�labilece�inin GARANT�S�N� veriyor. const'ta b�yle bir garanti yok.
	

	const int a = 10;
	const int b = 30;
	int c = 20;
	constexpr auto d = a + b; // legal, bir s�k�nt� yok. Her iki ifade de bir sabit
	constexpr auto e = a + c; // a sabit bir ifade fakat c const de�il bundan dolay� sabit ifade de de�il. Sentaks hatas�
	
	1:22
*/

