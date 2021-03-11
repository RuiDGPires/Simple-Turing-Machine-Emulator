NAME = tm
CC=g++
CFLAGS=-I.
DEPS = src/turingmachine.hpp
OFILES = turingmachine.o tmconfig.o tmstate.o
TEST_DEPS = src/catch.hpp
TEST_OFILES = catch.o test.o

MAIN_DEPS = ""
MAIN_OFILES = main.o 

%.o: %.c $(DEPS) $(MAIN_DEPS) $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OFILES) $(MAIN_OFILES)
	$(CC) -o $(NAME) $(OFILES) $(MAIN_OFILES) -lm

test: $(OFILES) $(TEST_OFILES)
	$(CC) -o $(NAME) $(OFILES) $(TEST_OFILES) -lm

clean:
	rm -f *.o $(NAME)
