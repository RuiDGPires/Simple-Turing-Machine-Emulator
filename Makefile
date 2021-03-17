NAME = tm
CC=g++
WCC=x86_64-w64-mingw32-g++
LFLAGS=-I.

CWX=`wx-config --cxxflags`
LWX=`wx-config --libs`

DEPS = src/turingmachine/include/*.hpp src/evaluator/include/*.hpp
OFILES = src/turingmachine/turingmachine.o src/turingmachine/tmconfig.o src/turingmachine/tmstate.o src/evaluator/evaluator.o src/evaluator/evaluator_parsing.o src/evaluator/filereader.o  src/evaluator/exceptions.o
CPPFILES= src/turingmachine/*.cpp src/evaluator/*.cpp

TEST_DEPS = src/catch/catch.hpp
TEST_OFILES = src/catch/catch.o src/test.o

MAIN_DEPS = ""
MAIN_OFILES = src/main.o
MAIN_CFILES = src/main.cpp

GUI_DEPS = src/gui/include/*.hpp
GUI_CPPFILES = src/gui/*.cpp
GUI_OFILES = src/gui/cApp.o src/gui/cMain.o

%.o: %.cpp $(DEPS) $(MAIN_DEPS) $(TEST_DEPS) $(GUI_DEPS)
	$(CC) -c $(LWX) -o $@ $< $(LFLAGS)  

all: $(OFILES) $(MAIN_OFILES)
	$(CC) $(OFILES) $(MAIN_OFILES) -o $(NAME) -lm 

gui: $(OFILES) $(GUI_DEPS)
	$(CC) $(OFILES) $(GUI_CPPFILES) $(CWX) $(LWX) -o $(NAME)_gui

test: $(OFILES) $(TEST_OFILES)
	$(CC) $(CWX) -o test $(OFILES) $(TEST_OFILES) -lm 

clean:
	rm -f  *.o src/**/*.o test $(NAME) $(NAME).exe 


windows: $(DEPS) 
	$(WCC) -o $(NAME).exe $(CPPFILES) $(MAIN_CFILES) -lm --static -static-libstdc++ 

wgui: $(DEPS) $(GUI_DEPS)
	$(WCC) -o $(NAME).exe $(CPPFILES) $(GUI_CPPFILES) -lm --static -static-libstdc++  $(CWX) $(LWX) 
