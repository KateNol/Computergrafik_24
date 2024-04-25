#include <stdio.h>
#include <math.h>
#include "utils/matrix_operations.hpp"
#include <cmath>



/*Funktion zur Erzeugung einer Einheitsmatrix = Identity
    um Ergebnis zu bekommen (mit nur 0en wäre alle = 0)
*/  
void identity(float *out) {
    if (out == NULL) {
        fprintf(stderr, "Fehler: NULL-Zeiger übergeben\n");
        return;
    }
    
    for (int i = 0; i < 16; ++i) {
        out[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
}

/*Funktion zur Translation einer Matrix
kleiner / größer / Position ändern/ drehen /  3.

*/ 
void translate(float *out, const float *in, const float *v) {
    if (out == NULL || in == NULL || v == NULL) {
        fprintf(stderr, "Fehler: NULL-Zeiger übergeben\n");
        return;
    }
    
    for (int i = 0; i < 16; ++i) {
        out[i] = in[i];
    }
    
    out[12] += v[0];
    out[13] += v[1];
    out[14] += v[2];
}

// Funktion zur Skalierung einer Matrix 1.
void scale(float *out, const float *in, const float *v) {
    if (out == NULL || in == NULL || v == NULL) {
        fprintf(stderr, "Fehler: NULL-Zeiger übergeben\n");
        return;
    }
    
    for (int i = 0; i < 16; ++i) {
        out[i] = in[i];
    }
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            out[i + 4 * j] *= v[i];
        }
    }
}

// Funktion zur Rotation um die z-Achse einer Matrix 2.
void rotatez(float *out, const float *in, float angle) {
    if (out == NULL || in == NULL) {
        fprintf(stderr, "Fehler: NULL-Zeiger übergeben\n");
        return;
    }
    
    for (int i = 0; i < 16; ++i) {
        out[i] = in[i];
    }
    
    float c = cosf(angle);
    float s = sinf(angle);
    
    float rotationMatrix[] = {
        c, -s, 0.0f, 0.0f,
        s, c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float result[16];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i * 4 + j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result[i * 4 + j] += out[i * 4 + k] * rotationMatrix[k * 4 + j];
            }
        }
    }
    
        for (int i = 0; i < 16; ++i) {
        out[i] = result[i];
        }
       
    }

    void normalize(float *out, float *a) {
        out[0]= (1/length(a))*(a[0]); //x
        out[1]= (1/length(a))*(a[1]); //y
        out[2]= (1/length(a))*(a[2]); //z
    }

    float length(float *vec3){
        
        return sqrt((vec3[0])*(vec3[0])+(vec3[1])*(vec3[1])+(vec3[2])*(vec3[2]));
    }

    float dot(float *a, float *b) { // b= a1*b1+a2*b2+a3*b3
          return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];

        }




    void lookAt(float *eye, float *look, float *up, float *out) { // crossproduct funktion schreiben
        float n [3];
        n [0]= eye[0]- look [0];
        n [1]= eye[1]- look [1];
        n [2]= eye[2]- look [2];

        //printf("%f %f %f \n\n",n[0],n[1],n[2]);
    
        float u [3];
        u [0] = (up[1] * n[2]) - (up[2]* n[1]);
        u [1] = (up[2] * n[0]) - (up[0]* n[2]);
        u [2] = (up[0] * n[1]) - (up[1]* n[0]);

        //Normalisierung: koord in cg von -1 --> +1 und die 600*800 pixel müssen darin abgebildet werden ( Länge des vektors auf 1 setzt)
         float nnorm [3];
         float unorm [3];
         //float vnorm [3];
        
         normalize(nnorm,n);
         normalize(unorm,u);
         //normalize(vnorm,v);
        

           float v [3];
        v [0] = (nnorm[1] * unorm[2]) - (n[2]* u[1]);
        v [1] = (nnorm[2] * unorm[0]) - (n[0]* u[2]);
        v [2] = (nnorm[0] * unorm[1]) - (n[1]* u[0]);

          

         float tx = -(dot(unorm ,eye));
         float ty = -(dot(v ,eye));
         float tz = -(dot(nnorm ,eye));

        


        /*
        create view Matrix:
        |  u'x  u'y  u'z  tx  |
        |  v'x  v'y  v'z  ty  |
        |  n'x  n'y  n'z  tz  |
        |    0    0    0   1  |
         */
          
         out[0] = unorm[0]; 
         out[1] = v[0];
         out[2] = nnorm[0];
         out[4] = unorm[1];
         out[5] = v[1];
         out[6] = nnorm[1];
         out[8] = unorm[2];
         out[9] = v[2];
         out[10]= nnorm[2];
         out[12] = tx;
         out[13] = ty;
         out[14] = tz;

        
    }

        


