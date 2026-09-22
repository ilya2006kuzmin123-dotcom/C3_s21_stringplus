CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -Wno-format

SRC=$(wildcard code/s21_*.c)
TSRC = $(wildcard tests/s21_test_*.c) tests/s21_tests.c

OBJ=$(SRC:code/%.c=code/%.o)
TOBJ=$(TSRC:tests/%.c=tests/%.o)

LIB_NAME=s21_string.a
NAME=s21_string
UNAME=$(shell uname -s)

ifeq ($(UNAME), Linux)
	LIBS=-lcheck -lm -lrt -lpthread -lsubunit
endif
ifeq ($(UNAME), Darwin)
	LIBS=-lcheck
endif

all: clean $(LIB_NAME) test gcov_report

clean:
	rm -rf code/*.o tests/*.o s21_string report coverage.info *.o *.gcda *.gcno s21_tests $(LIB_NAME)

test: $(OBJ) $(TOBJ)
	$(CC) $(OBJ) $(TOBJ) $(CFLAGS) -o $(NAME) $(LIBS)
	./$(NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

code/%.o: code/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean $(LIB_NAME) test

check_style:
	clang-format -n --style="Google" code/*.c tests/*.c *.h

fix_style:
	clang-format -i --style="Google" code/*.c tests/*.c *.h

gcov_report:
	$(CC) $(CFLAGS) --coverage $(SRC) $(TSRC) $(LIBS) -o s21_tests
	./s21_tests
	lcov --capture --directory . --output-file coverage.info --rc lcov_branch_coverage=1
	genhtml coverage.info --output-directory report
	@echo "Report generated in report/index.html"