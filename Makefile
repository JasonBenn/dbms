TEST_DB=../bradfield/databases/ciadocs/1.csv
# TODO: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

default:
	clear
	clang ./main.c -o main.o
	./main.o $(TEST_DB)

develop:
	wach --only *.[ch], "clear && cc main.c -o main.o && ./main.o $(TEST_DB)"

debug:
	clang -g -O0 main.c -o main-debug.o
	lldb -- ./main-debug.o ~/code/bradfield/databases/ciadocs/1.csv
