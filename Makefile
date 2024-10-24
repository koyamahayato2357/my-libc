test:
	clang -std=c23 -DTEST_MODE *.c
	./a.out

debug:
	clang -std=c23 -DTEST_MODE *.c -g

analyze:
	clang-tidy *.c -- -std=c23 -DTEST_MODE
