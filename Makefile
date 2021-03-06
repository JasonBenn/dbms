TEST_DB = tests/stub-data.csv

# Adds include dir to the preprocessor search path (for #include'd files)
CFLAGS = -I include

# all: run


# --- Building object files

build/commands.o: commands/load-csv.c
	clang $(CFLAGS) commands/load-csv.c -c -o build/commands.o

build/executor.o: executor/seq-scan.c
	clang $(CFLAGS) executor/seq-scan.c -c -o build/executor.o

build/utils.o: utils/utils.c
	clang $(CFLAGS) utils/utils.c -c -o build/utils.o


OBJS = build/commands.o build/executor.o build/utils.o

compile:
	clang $(CFLAGS) $(OBJS) main/main.c -o build/main.o

run: main/main.c $(OBJS)
	clang $(CFLAGS) $(OBJS) main/main.c -o build/main.o
	build/main.o $(TEST_DB)

# --- Entry points

test:
	clang $(CFLAGS) $(OBJS) tests/test.c -o build/test.o
	build/test.o

debug:
	clang $(CFLAGS) $(OBJS) -g -O0 main/main.c -o build/main-debug.o
	lldb -- build/main-debug.o $(TEST_DB)

debug_test:
	clang $(CFLAGS) $(OBJS) -g -O0 tests/test.c -o build/test-debug.o
	lldb -- build/test-debug.o $(TEST_DB)

clean:
	rm build/*.o
