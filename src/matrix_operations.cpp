#include <stdio.h>
#include <math.h>
#include "matrix_operations.hpp"



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