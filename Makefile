NAME = tm
CC=g++
WCC=x86_64-w64-mingw32-g++
CFLAGS=-I.
DEPS = src/turingmachine/turingmachine.hpp src/evaluator/evaluator.hpp src/evaluator/exceptions.hpp
OFILES = src/turingmachine/turingmachine.o src/turingmachine/tmconfig.o src/turingmachine/tmstate.o src/evaluator/evaluator.o src/evaluator/evaluator_parsing.o src/evaluator/filereader.o  src/evaluator/exceptions.o
CPPFILES= src/turingmachine/turingmachine.cpp src/turingmachine/tmconfig.cpp src/turingmachine/tmstate.cpp src/evaluator/evaluator.cpp src/evaluator/evaluator_parsing.cpp src/evaluator/filereader.cpp  src/evaluator/exceptions.cpp
TEST_DEPS = src/catch/catch.hpp
TEST_OFILES = src/catch/catch.o src/test.o

MAIN_DEPS = ""
MAIN_OFILES = src/main.o
MAIN_CFILES = src/main.cpp

%.o: %.c $(DEPS) $(MAIN_DEPS) $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OFILES) $(MAIN_OFILES)
	$(CC) -o $(NAME) $(OFILES) $(MAIN_OFILES) -lm

test: $(OFILES) $(TEST_OFILES)
	$(CC) -o test $(OFILES) $(TEST_OFILES) -lm

clean:
	rm -f  *.o src/*.o src/catch/*.o src/turingmachine/*.o $(NAME) $(name).exe


windows: $(DEPS) 
	$(WCC) -o $(NAME).exe $(CPPFILES) $(MAIN_CFILES) -lm --static -static-libstdc++
