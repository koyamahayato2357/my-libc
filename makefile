test:
	clang-20 -std=c2y -DTEST_MODE *.c -g3 -Wall -Wextra
	./a.out
