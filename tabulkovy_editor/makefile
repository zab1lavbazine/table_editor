


PROGRAM=tabulkovy_editor

CC=g++

CXXFLAGS=-std=c++11 -pedantic -Wall -Wextra -g -Wno-long-long -O0 -ggdb

all: compile doc

run: $(PROGRAM)
	./$(PROGRAM) 

compile: $(PROGRAM)

doc: src/main.cpp src/Table/cell.cpp src/include/cell.h src/DataTypes/number.cpp src/include/number.h src/include/object.h src/Table/table.cpp src/include/table.h src/DataTypes/text.cpp src/include/text.h
	

$(PROGRAM) : src/objs/main.o  src/objs/number.o  src/objs/text.o src/objs/cell.o src/objs/table.o
	$(CC) $(CXXFLAGS) $^ -o $@


src/objs/main.o: src/main.cpp src/include/cell.h src/include/number.h src/include/object.h src/include/table.h src/include/text.h
	$(CC) $(CXXFLAGS) -c $< -o $@

src/objs/number.o: src/DataTypes/number.cpp src/include/number.h src/include/object.h
	$(CC) $(CXXFLAGS) -c $< -o $@

src/objs/text.o: src/DataTypes/text.cpp src/include/text.h src/include/object.h
	$(CC) $(CXXFLAGS) -c $< -o $@

src/objs/cell.o: src/Table/cell.cpp src/include/cell.h src/include/number.h src/include/object.h src/include/text.h
	$(CC) $(CXXFLAGS) -c $< -o $@

src/objs/table.o: src/Table/table.cpp src/include/table.h src/include/cell.h src/include/number.h src/include/object.h src/include/text.h
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) objs/*.o 


