test:
	clang -std=c23 -DTEST_MODE *.c -Wall -Wextra
	./a.out

all-test:
	clang -std=c23 -DTEST_MODE -DTEST_MODE_ALL *.c -Wall -Wextra
	./a.out

debug:
	clang -std=c23 -DTEST_MODE *.c -g -Wall -Wextra

analyze:
	clang-tidy *.c -- -std=c23 -DTEST_MODE -Wall -Wextra -fsanitize=address
