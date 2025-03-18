#pragma once
#ifdef __cplusplus
extern "C" {
#endif

	int foo(int, int);
	int bar(int, double);
	int baz(char, char);
	int bom(long, int);

#ifdef __cplusplus
}
#endif

extern "C" {
	int foo(int, int);
	int bar(int, double);
	int baz(char, char);
	int bom(long, int);
}