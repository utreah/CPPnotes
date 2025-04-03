class Eng {
public:
	void foo(); // non-const
	void bar()const; // 
	int mx;
};
/*
	Yukarýdaki foo fonksiyonlarýnýn gizli parametreleri þu þekilde
	void foo(Eng*); //non-const
	void bar(const Eng*)const;  // const
*/
void Eng::foo() {
	bar(); // Burada T* türünden const T* türüne bir dönüþüm var. Logical const oluyor. Sentaks hatasý yok
}
void Eng::bar()const{ 
	foo(); // Burada const T* türünden T* türüne dönüþüm var. Sentaks hatasý var
}
