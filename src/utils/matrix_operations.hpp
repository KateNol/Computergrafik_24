#ifndef MATRIX_OPERATIONS_HPP
#define MATRIX_OPERATIONS_HPP

#include <stdio.h>
#include <math.h>

void identity(float *out);
void translate(float *out, const float *in, const float *v);
void scale(float *out, const float *in, const float *v);
void rotatez(float *out, const float *in, float angle);

#endif /* MATRIX_OPERATIONS_HPP */
