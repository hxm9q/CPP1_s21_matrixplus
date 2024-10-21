CPP = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra
TEST = -lgtest -lgtest_main -pthread
COVERAGE = -fprofile-arcs -lcheck -ftest-coverage

all: s21_matrix_oop.a

s21_matrix_oop.a: 
	$(CPP) $(CPPFLAGS) -c *.cpp
	ar rc s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a

test: s21_matrix_oop.a
	$(CPP) $(CPPFLAGS) -o tests test.cpp s21_matrix_oop.a $(TEST) $(COVERAGE)
	./tests

gcov_report: test
	gcov -f *.gcda
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info  

style: 
	clang-format --style=Google -n *.cpp *.h

clean: 
	@rm -rf test *.o *.a *.gcov *.gcda *.gcno *.info


#docker build -t test .
#docker run -it test /bin/bash