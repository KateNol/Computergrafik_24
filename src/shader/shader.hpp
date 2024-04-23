#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <stdio.h>

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

GLuint compileShader(GLenum type, const char* source);
GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);

#endif /* SHADER_HPP */
