TEST_DB = tests/stub-data.csv

# Adds include dir to the preprocessor search path (for #include'd files)
CFLAGS = -I include

all: main


# --- Building object files

commands.o: commands/load-csv.c
	clang $(CFLAGS) commands/load-csv.c -c -o commands.o

executor.o: executor/seq-scan.c
	clang $(CFLAGS) executor/seq-scan.c -c -o executor.o

utils.o: utils/utils.c
	clang $(CFLAGS) utils/utils.c -c -o utils.o

OBJS = commands.o executor.o utils.o


# --- Entry points

main: $(OBJS)
	clang $(CFLAGS) $(OBJS) main.c -o main.o
	main.o $(TEST_DB)

test:
	clang $(CFLAGS) $(OBJS) tests/test.c -o test.o
	test.o

debug_main:
	clang $(CFLAGS) $(OBJS) -g -O0 main.c -o main-debug.o
	lldb -- main-debug.o $(TEST_DB)

debug_test:
	clang $(CFLAGS) $(OBJS) -g -O0 tests/test.c -o test-debug.o
	lldb -- test-debug.o $(TEST_DB)

clean:
	rm *.o
