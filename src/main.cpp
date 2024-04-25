#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "utils/matrix_operations.hpp"
#include "shader/shader.hpp"



#define M_PI 3.14159265358979323846
 static int indexSize =0;




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
        //GLfloat scaleVector[3] = {0.7f, 0.3f, 1.0f};
        //scale(transformMatrix, transformMatrix, scaleVector);
        //rotatez(transformMatrix, transformMatrix, angle); 
        //GLfloat transVector[3] = {0.0f, 0.0f, 0.0f};
        //translate(transformMatrix, transformMatrix,transVector);

        // Transformationsmatrix an den Shader übergeben
        GLint transformLocation = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transformMatrix); // scallierte/rotierte/transl Matrix an den Vertexshader übergeben
      
        //view-Matrix an den Shader übergeben
        GLfloat viewMatrix[16];
        identity(viewMatrix);
        
        float eye[3]={0.0f,0.0f,3.0f}; //Ursprung der Kamera
        float look[3]= {0.0f,0.0f,0.0f};//Blickrichtung
        float up[3]= {0.0f,1.0f,0.0f}; //nach oben
        lookAt(eye,look,up,viewMatrix);

        for (int i = 0; i < 16; i++) {
            printf("%f, ",viewMatrix[i]);
        }
        printf("\n\n");
        
        GLint viewLocation = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix);

        // Dreieck rendern
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

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

        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, 0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, 0.5, 0.5,
        -0.5, -0.5, 0.5,
    
    };

    GLuint indices [] = {
        
    5,3,1, 
    3,8,4,
    7,6,8,
    2,8,6,
    1,4,2,
    5,2,6,
    5,7,3,
    3,7,8,
    7,5,6,
    2,4,8,
    1,3,4,
    5,1,2,

    };

    indexSize = sizeof(indices)/sizeof(GLuint);
    

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
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        3 * sizeof(GLfloat),         // stride and tells us the space between consecutive vertex attributes
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