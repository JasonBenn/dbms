TEST_DB = ../bradfield/databases/ciadocs/1.csv

main.o test.o: %.c:
	@clang tests/test.c -o build/test.o
	@build/test.o
	@clang main.c -o build/main.o
	@build/main.o $(TEST_DB)

debug:
	@clang -g -O0 main.c -o build/main-debug.o
	@lldb -- build/main-debug.o $(TEST_DB)

test:
	@clang ./tests/test.c -o build/test.o
	@build/test.o
