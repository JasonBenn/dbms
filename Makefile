TEST_DB=../bradfield/databases/ciadocs/1.csv
# TODO: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

default:
	@./main.out $(TEST_DB)

develop:
	wach --only *.c, "clear && cc main.c -o main.out && ./main.out $TEST_DB"
