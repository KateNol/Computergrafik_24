GLEW_LIBS=$(shell pkgconf glew --libs)
GLFW_LIBS=$(shell pkgconf glfw3 --libs)

PROGRAMM_NAME = CG1


CC = g++
SRC = src
BIN = bin
OBJ = obj

TARGET = $(BIN)/$(PROGRAMM_NAME)
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(GLEW_LIBS) $(GLFW_LIBS)

obj/%.o: $(SRC)/%.cpp
	g++ -c $< -o $@

clean:
	rm $(BIN)/* $(OBJ)/*