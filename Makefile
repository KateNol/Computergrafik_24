PROGRAMM_NAME = Gomputergrafik_24_OpenGL

GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw

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