TARGET = pathLib

$(TARGET): pathLib.a
	g++ $^ -o $@

pathLib.a: pathLib.o platform.o
	ar rcs $@ $^

pathLib.o: pathLib.cpp include/pathLib.hpp
	g++ -c -o $@ $<

platform.o: platform.c platform.h
	g++ -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
