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
					int foo(int);
					foo = 5; // name lookup foo'yu bulacak, fakat context control enseye vuracak.
				access control -> kullan�l�p kullan�lmayaca��n�n kontrol�, public private vs
�sim arama bir s�ra dahilinde  yap�l�r.
	- �nce kullan�ld��� blo�un i�ine bak.
	- Bulunamazsa, onu kapsayan blo�(klara)a bak
	- Global namespacede araa
Aranan isim bulununca sona erer. 
24:00

*/