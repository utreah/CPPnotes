#pragma once
#include <ostream>
#include <istream>
/*
	istream ve ostream fonksiyonlarýný(sýnýf içindeki) bir baþlýk dosyasýnda tanýmlar isek ostream ve istream baþlýk dosyalarýný include etmek
		zorundayýz ki bu da compile timeda azda olsa yavaþlýða sebep olacak.
		iosfwd(input output forward declarations) baþlýk dosyasý - light header - yani içerisinde sadece forward declarationlarý var.
			Bu da daha hýzlý derlenmesini saðlýyor. 
*/



class Mint {
public:
	Mint() = default;
	explicit Mint(int x) : mval{ x } {}
	 

	friend Mint [[nodiscard]]operator+(const Mint& lhs, const Mint& rhs) {
		Mint temp(lhs);
		temp += rhs;
		return temp;
		// veya aþaðýdaki þekilde de yazýlabilir ayný þey. Burada temp object kullanýyoruz
		// return Mint(lhs) += rhs;
	}
	friend Mint [[nodiscard]] operator-(const Mint& lhs, const Mint& rhs) {
		return Mint(lhs) -= rhs;
	}
	friend Mint [[nodiscard]] operator*(const Mint& lhs, const Mint& rhs) {
		return Mint(lhs) *= rhs;

	}
	friend Mint [[nodiscard]] operator/(const Mint& lhs, const Mint& rhs) {
		return Mint(lhs) /= rhs;

	}

	friend bool operator==(const Mint& lhs, const Mint& rhs) {
		return lhs.mval == rhs.mval;
	}
	friend bool operator!=(const Mint& lhs, const Mint& rhs) {
		return !(lhs == rhs);
		// return !operator(lhs, rhs);
	}
	friend bool operator<(const Mint& lhs, const Mint& rhs);
	friend bool operator<=(const Mint& lhs, const Mint& rhs);
	friend bool operator>(const Mint& lhs, const Mint& rhs);
	friend bool operator>=(const Mint& lhs, const Mint& rhs);


	// mutators
	Mint& operator+=(const Mint& other) {
		mval += other.mval;
		return *this;
	}
	Mint& operator-=(const Mint& other) {
		mval -= other.mval;
		return *this;
	}
	Mint& operator*=(const Mint& other) {
		mval *= other.mval;
		return *this;
	}
	Mint& operator/=(const Mint& other) {
		mval /= other.mval;
		return *this;
	}
	Mint& operator%=(const Mint& other) {
		mval %= other.mval;
		return *this;
	}

	// formatted input-output
	friend std::ostream& operator<<(std::ostream& os, const Mint& m) {
		return os << "[" << m.mval << "]" << "\n";
	}
	// ikinci parametre const deðil çünkü input streaminden aldýðýmýz deðerler ona verilecek. 
	friend std::istream& operator>>(std::istream& is, Mint& m) {
		return is >> m.mval;
	}

private:
	int mval;
};


