class testClass {
public:
	void foo(int x, int y);
	void bar(int x);
};
void testClass::foo(int x, int y) {
	bar(x);
	bar(y);
	/*
		Burada bar fonksiyonuna foo içerisinde örtülü olarak tutulan testClass* pointerýda veriliyor.
		Eðer derleyici bar adýnda bir nesnenin ismini block scopeta bulamaz ise globalde aramak yerine
			class scopeta arayacak. Hem foo hem bar ayný sýnýf türünden nesnenin adresini kullanarak çaðrýlacak
		Global namespacete bar isminde bir fonksiyon olmasý önemli deðil. Ýlk olarak class scopeta arayacaðý için
			global function name masking'e uðrayacak.
	*/
	foo(x - 1, y - 1); // recursive member function call
}
