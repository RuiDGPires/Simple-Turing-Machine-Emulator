NAME = tm
CC=g++
CFLAGS=-I.
DEPS = src/turingmachine/turingmachine.hpp src/evaluator/evaluator.hpp src/evaluator/exceptions.hpp
OFILES = src/turingmachine/turingmachine.o src/turingmachine/tmconfig.o src/turingmachine/tmstate.o src/evaluator/evaluator.o src/evaluator/filereader.o  src/evaluator/exceptions.o
TEST_DEPS = src/catch/catch.hpp
TEST_OFILES = src/catch/catch.o src/test.o

MAIN_DEPS = ""
MAIN_OFILES = src/main.o 

%.o: %.c $(DEPS) $(MAIN_DEPS) $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OFILES) $(MAIN_OFILES)
	$(CC) -o $(NAME) $(OFILES) $(MAIN_OFILES) -lm

test: $(OFILES) $(TEST_OFILES)
	$(CC) -o $(NAME) $(OFILES) $(TEST_OFILES) -lm

clean:
	rm -f  *.o src/*.o src/catch/*.o src/turingmachine/*.o $(NAME)
