CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -Wno-format -std=c11
SRC=code/*.c
OBJ=$(SRC:.c=.o)
TSRC=tests/*.c
TOBJ=$(TSRC:.c=.o)
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
	rm -rf $(OBJ) $(TOBJ) s21_string report coverage.info *.o *.gcda *.gcno s21_tests $(LIB_NAME)

test: $(OBJ) $(TOBJ)
	$(CC) $^ $(CFLAGS) -o $(NAME) $(LIBS)
	./$(NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^
	mv *.o s21_string_functions

$(TOBJ): $(TSRC)
	$(CC) $(CFLAGS) -c $^
	mv *.o tests

rebuild: clean $(LIB_NAME) test

check_style:
	clang-format -n --style="Google" s21_string_functions/*.c s21_string_functions/*.h tests/*.c *.h

fix_style:
	clang-format -i --style="Google" s21_string_functions/*.c s21_string_functions/*.h tests/*.c *.h

gcov_report:
	$(CC) $(CFLAGS) --coverage $(SRC) $(TSRC) $(LIBS) -o s21_tests
	./s21_tests
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory report
	open report/index.html