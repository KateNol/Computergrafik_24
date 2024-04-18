#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "matrix_operations.hpp"
#include "shader.cpp"


#define M_PI 3.14159265358979323846





void draw(GLuint VAO, GLuint shaderProgram) {

     // Hintergrund löschen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Shader-Programm verwenden
        glUseProgram(shaderProgram);

        /*
        Transformationsmatrix erstellen (hier: Rotation um die z-Achse)
        mit allen Funktionen werden neue transMatrizen erstellt die dan mittels 
        Vertexshader das Dreieck mit den entpsrechenden Weten darstellen
        
        */ 
        float angle = (GLfloat)glfwGetTime() * M_PI / 4.0f;
        float transformMatrix[16]; //sind alle Operationen gespeichert 
        identity(transformMatrix); // die baue ich als Einheitsmatrix (damit keine 0en)
        GLfloat scaleVector[3] = {0.7f, 0.3f, 1.0f};
        scale(transformMatrix, transformMatrix, scaleVector);
        rotatez(transformMatrix, transformMatrix, angle); 
        GLfloat transVector[3] = {0.0f, 0.0f, 0.0f};
        translate(transformMatrix, transformMatrix,transVector);

        // Transformationsmatrix an den Shader übergeben
        GLint transformLocation = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transformMatrix); // scallierte/rotierte/transl Matrix an den Vertexshader übergeben
      
        // Dreieck rendern
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
     
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // Frame-Puffer austauschen und Ereignisse verarbeiten
        
}


int main() {
    // GLFW initialisieren
    if (!glfwInit()) {
        fprintf(stderr, "Fehler beim Initialisieren von GLFW\n");
        return -1;
    }



    // GLFW Window erstellen
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Fehler beim Erstellen des Fensters\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLEW initialisieren
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Fehler beim Initialisieren von GLEW\n");
        return -1;
    }

    // Vertex-Array-Object und Vertex-Buffer-Object erstellen
    GLuint VAO, VBO, EBO; //neu
    
     GLfloat vertices[] = {
             //   x   y
             -0.4, -0.3,  //links unten  0 unique
             -0.2, -0.3,  // rechts unten 1
             -0.4,  0.7,  // links oben 2
             -0.2,  0.7,  // rechts oben 3 unique


              0.2,  0.7,  // links oben 4 unique
              0.2, -0.3,  // links unten 5
              0.4,  0.7,  // rechts oben 6
              0.4, -0.3,  // rechts unten 7 unique

              -0.2, 0.3,
              -0.2, 0.1,
               0.2, 0.3,
               0.2, 0.1,
    
};

    GLuint indices [] = {
        
    0, 1, 2,  // Erstes Dreieck des ersten Vierecks
    3, 2, 1,  // Zweites Dreieck des ersten Vierecks
    4, 5, 6,  // Erstes Dreieck des zweiten Vierecks
    7, 5, 6,   // Zweites Dreieck des zweiten Vierecks
    8, 9, 10,
    11,10,9

    };

    

// Neue Vertex-Daten für ein Viereck  // gepsiegelt
   
// VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for Position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &(vertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader  
        2,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        2 * sizeof(GLfloat),         // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);
 
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
    

   // Shader Prog aufrufen

    GLuint shaderProgram = createShaderProgram(vertexShaderSource,fragmentShaderSource);
    if(shaderProgram == 0) {
        return -1;
    }
    
    
   
    
   
    // Haupt-Render-Loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        draw(VAO, shaderProgram);

         glfwSwapBuffers(window);

    }

  

    // Aufräumen
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}