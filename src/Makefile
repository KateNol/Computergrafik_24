GLEW_LIBS=$(shell pkgconf glew --libs)
GLFW_LIBS=$(shell pkgconf glfw3 --libs)

cg1: main.cpp
	gcc -o cg1 main.cpp shader.cpp matrix_operations.cpp $(GLEW_LIBS) $(GLFW_LIBS) -lm

