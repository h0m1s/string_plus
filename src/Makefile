CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11 
LDFLAGS=-lcheck -lsubunit -lm -lpthread
S21_C=$(wildcard s21_*.c)

all: s21_string.a test gcov_report

s21_string.a:
	$(CC) -fprofile-arcs -ftest-coverage $(CFLAGS) $(S21_C)
	ar r s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: s21_string.a test.c
	$(CC) -fprofile-arcs -ftest-coverage test.c s21_string.a -o test $(LDFLAGS)
	./test

gcov_report: s21_string.a test.c
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage test.c
	$(CC) test.o s21_string.a -o test $(LDFLAGS) -fprofile-arcs -ftest-coverage
	./test
	gcovr -r . --html-details -o gcov_report.html
	open gcov_report.html

clean:
	rm *.a test *.html *.css *.gcda *.gcno *.o
