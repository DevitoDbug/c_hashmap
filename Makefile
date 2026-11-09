run: 
	clang -Wall -Wextra -fsanitize=address -o0 -g main.c -o out
	./out

.PHONY: run
