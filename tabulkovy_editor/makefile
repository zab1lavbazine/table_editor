


CC=g++

CXXFLAGS=-std=c++11 -pedantic -Wall -Wextra -g -Wno-long-long -ggdb -fsanitize=address

BIN_DIR = bin
SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs

#List of all source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
#List of all header files
DEPS := $(wildcard $(INC_DIR)/*.h)
#List of object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
#Name of the executable
PROGRAM = $(BIN_DIR)/tabulkovy_editor


doc:
	doxygen doc/Doxyfile


all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@


run : $(PROGRAM)
	./$(PROGRAM)


clean: 
	rm -f $(OBJ_DIR)/*.o $(PROGRAM)
