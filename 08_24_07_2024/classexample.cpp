#include "classexample.h"
/*
	Unqualified Name: Eðer bir isim herhangi bir sýnýf adý, ad alaný(namespace)
		gibi bir þeyle açýkça belirtilmeden doðrudan kullanýlýyorsa, buna unqualified name denir.

	Qualified Name: Eðer bir isim, bir sýnýf adý (Eng::mx), ad alaný (std::vector), 
		gibi bir ön ek ile belirtiliyorsa, bu durumda qualified name olur.
*/
/*
	Name lookup kurallarý member functinlar için farklý iþliyor.
	Global/free fonksiyonlarda name lookup çalýþýrken;
		-Bulunduðu blok içerisinde bildiriminden önce
		-Kapsayan blok(lar) içerisinde arýyor. Eðer bulamazsa;
		-Global namespace/File scopeta arýyor.
	Member functionlarda ise;
		-Bulunduðu blok içerisinde bildiriminden önce
		-Kapsayan blok(lar) içerisinde arýyor. Eðer bulamazsa;
		-Fonksiyon tanýmý hangi sýnýfa ait ise o sýnýfýn içerisinde arýyor.
*/
void Eng::set(int x, int y) {
	mx = x;
	my = y;
	/*
		mx ve my unqualified isim. member function olduðu için, Önce Eng::set fonksiyonunun bloðu içerisinde arayacak,
			bulamadýðýnda ise Eng sýnýfý içerisinde arayacak ve private non-static data member olduðunu görecek
			ve name lookup sonlanacak. 
	*/
}
void set2(int x, int y) {
	// Eng sýnýfýnýn içerisindeki data memberlarýn isimlerinin x ve y olduðunu farz et.
	x = x;
	y = y;
	/*
		Name lookup önce bulunduðu blok içeirsine bakacak ve parametre deðiþkenleri olan x ve y isimlerini bulacak.
		Yani burada parametre deðiþkeni olan x'e x in deðeri, y'ye y'nin deðeri set ediliyor. :D
	*/
}
int x = 10;
void Eng::set3(int x, int y) {
	mx = x; // Burada parametre deðiþkeni olan x'in deðeri mx'e set ediliyor.
	mx = ::x; // Burada unary prefix scope resolution ile global namespacede bulunan x'in deðeri mx'e set ediliyor.
	mx = x + ::x; // parametre x ve global x'in deðerleri mx'e set ediliyor.

	/*
		Burada ::x bir qualified isim. Çünkü nerede tanýmlandýðý scope resolution ile belirtiliyor.
	*/
}
void set4(Nec* p, int x, int y) {
	p->mx = x;
	p->my = y; 
	/*
		mx ve my burada qualified name. Eng sýnýf türünün içerisinde aranmasýný söylüyoruz.
	*/
}
/*
	Arrow operator, dot operator, unary prefix scope resolution gibi operatörlerin kullanýlmasý
		name lookup sürecini direkt olarak etkiliyor. Sonuçta bu operatörleri kullandýðýmýzda derleyiciye
		isimleri hangi scopeta aramasýný söylüyoruz. Tek tek tüm scopelarý gezmek zorunda kalmýyor. 
*/
int main() {
	/*
	
	Eng::set(12, 4); // sentaks hatasý veriyor çünkü set member fonksiyonu, non statik olduðu için
					// set fonksiyonuna sadece o sýnýf türünden bir nesne ile eriþilebilir. Çünkü set fonksiyonu
					// Eng* türünden bir nesnenin adresini almalý.
	Eng myeng;
	myeng.set(12, 4); // sentaks hatasý yok çünkü myeng'in adresi set fonksiyonuna gönderilebilir.
	*/
}