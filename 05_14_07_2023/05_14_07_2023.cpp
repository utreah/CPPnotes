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
					int foo(int);
					foo = 5; // name lookup foo'yu bulacak, fakat context control enseye vuracak.
				access control -> kullanýlýp kullanýlmayacaðýnýn kontrolü, public private vs
Ýsim arama bir sýra dahilinde  yapýlýr.
	- Önce kullanýldýðý bloðun içine bak.
	- Bulunamazsa, onu kapsayan bloð(klara)a bak
	- Global namespacede araa
Aranan isim bulununca sona erer. 
24:00

*/