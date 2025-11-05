class Bigint {

};
Bigint operator*(const Bigint&, const Bigint&);
Bigint operator+(const Bigint&, const Bigint&);
Bigint operator&(const Bigint&, const Bigint&);
int main() {
	Bigint b1, b2, b3, b4, b5;
	auto bx = b1 * b2 + b3 * b4 & b5;
	// auto bx = ((b1 * b2) + (b3 * b4)) & b5;

}