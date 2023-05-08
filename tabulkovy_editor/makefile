
CC=g++
CXXFLAGS=-Wall -pedantic -g
LDFLAGS=-fsanitize=address

SOURCE=main.cpp $(wildcard DataTypes/*.cpp) $(wildcard Table/*.cpp)
OBJECTS=$(addpefix compiled/, $(notdir $(SOURCE:.cpp=.o)))

all: $(OBJECTS) main.out

main.out: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

.cpp .o:
	$(CC) $(CXXFLAGS) -c $< -o compiled/$(notdir $@)

clean:
	rm -f *.o *.out

run: main.out
	./main.out

# main.o: main.cpp  
# 	g++ $(CXXFLAGS) -c main.cpp

# table.o: table.cpp table.h cell.h text.h number.h object.h
# 	g++ $(CXXFLAGS) -c table.cpp

# cell.o : cell.cpp cell.h text.h number.h object.h
# 	g++ $(CXXFLAGS) -c cell.cpp

# number.o : number.cpp number.h object.h
# 	g++ $(CXXFLAGS) -c number.cpp

# text.o : text.cpp text.h object.h
# 	g++ $(CXXFLAGS) -c text.cpp

# main.out: main.o  text.o  number.o cell.o table.o
# 	g++ $(LDFLAGS) main.o text.o number.o cell.o table.o -o main.out


# run: main.out
# 	./main.out

# clean:
# 	rm -f *.o *.out