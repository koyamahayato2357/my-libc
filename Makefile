test:
	clang -std=c23 -DTEST_MODE *.c -Wall -Wextra
	./a.out

debug:
	clang -std=c23 -DTEST_MODE *.c -g -Wall -Wextra

analyze:
	clang-tidy *.c -- -std=c23 -DTEST_MODE -Wall -Wextra
