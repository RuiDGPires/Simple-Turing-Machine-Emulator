NAME = tm
CC=g++
WCC=x86_64-w64-mingw32-g++
LFLAGS=-I. $(LWX)

CWX=`wx-config --libs`
LWX=`wx-config --cxxflags`

DEPS = src/turingmachine/turingmachine.hpp src/evaluator/*.hpp
OFILES = src/turingmachine/turingmachine.o src/turingmachine/tmconfig.o src/turingmachine/tmstate.o src/evaluator/evaluator.o src/evaluator/evaluator_parsing.o src/evaluator/filereader.o  src/evaluator/exceptions.o
CPPFILES= src/turingmachine/*.cpp src/evaluator/*.cpp

TEST_DEPS = src/catch/catch.hpp
TEST_OFILES = src/catch/catch.o src/test.o

MAIN_DEPS = ""
MAIN_OFILES = src/main.o
MAIN_CFILES = src/main.cpp

GUI_OFILE = src/

%.o: %.c $(DEPS) $(MAIN_DEPS) $(TEST_DEPS)
	$(CC) -c -o $@ $< $(LFLAGS) 

all: $(OFILES) $(MAIN_OFILES)
	$(CC) $(OFILES) $(MAIN_OFILES) -o $(NAME) -lm 

gui: $(OFILES) $(MAIN_OFILES)
	$(CC) $(OFILES) $(MAIN_OFILES) $(CWX) -o $(NAME) -lm 


test: $(OFILES) $(TEST_OFILES)
	$(CC) $(CWX) -o test $(OFILES) $(TEST_OFILES) -lm 

clean:
	rm -f  *.o src/*.o src/turingmachine/*.o test $(NAME) $(NAME).exe 


windows: $(DEPS) 
	$(WCC) $(LWX) $(CWX) -o $(NAME).exe $(CPPFILES) $(MAIN_CFILES) -lm --static -static-libstdc++ 
