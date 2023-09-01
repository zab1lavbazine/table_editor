


CC=g++

CXXFLAGS=-std=c++17 -pedantic -Wall -Wextra -g -Wno-long-long -ggdb -fsanitize=address

BIN_DIR = bin
DOC_DIR = doc
SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs
USERNAME = bareldan

#List of all source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
#List of all header files
DEPS := $(wildcard $(INC_DIR)/*.h)
#List of object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
#Name of the executable
PROGRAM = $(BIN_DIR)/$(USERNAME)


#create 'doc' directory 
$(shell mkdir -p $(DOC_DIR) $(OBJ_DIR) $(BIN_DIR))


doc:
	doxygen Doxyfile


compile: $(PROGRAM)
# $(OBJS)
#	$(CC) $(CXXFLAGS) $^ -o $(USERNAME)



all: $(PROGRAM) doc

$(PROGRAM): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@


run : $(PROGRAM)
	./$(PROGRAM)


clean: 
	rm -rf $(OBJ_DIR)/*.o $(PROGRAM) $(DOC_DIR)
