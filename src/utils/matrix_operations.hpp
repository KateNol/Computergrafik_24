#ifndef MATRIX_OPERATIONS_HPP
#define MATRIX_OPERATIONS_HPP

#include <stdio.h>
#include <math.h>

// Funktion zur Erzeugung einer Einheitsmatrix
void identity(float *out);

// Funktion zur Translation einer Matrix
void translate(float *out, const float *in, const float *v);

// Funktion zur Skalierung einer Matrix
void scale(float *out, const float *in, const float *v);

// Funktion zur Rotation um die z-Achse einer Matrix
void rotatez(float *out, const float *in, float angle);

// Funktion zur Normalisierung eines Vektors
void normalize(float *out, float *a);

// Funktion zur Berechnung der Länge eines Vektors
float length(float *vec3);

// Funktion zur Berechnung des Skalarprodukts zweier Vektoren
float dot(float *a, float *b);

// Funktion zur Berechnung einer View-Matrix basierend auf Eye, Look und Up Vektoren
void lookAt(float *eye, float *look, float *up, float *out);

// Funktion zur Berechnung einer Perspektiv-Projektionsmatrix
void perspective(float *out, float fovy, float aspect, float near, float far);

#endif /* MATRIX_OPERATIONS_HPP */
