#include "Complex.h"
#include <stdio.h>
#include <math.h>

int main() {
    struct Complex c = Complex.new(1.0, 2.0);
    struct Complex d = Complex.new(3.0, 4.0);
    struct Complex e = c.mul(&c, &d);
    struct Complex f = c.add(&c, &d);
    struct Complex g = c.sub(&c, &d);
    printf("Complex number: %.1f + %.1fi\n", c.re, c.im);
    printf("Absolute value: %.2f\n", c.abs(&c));
    printf("Multiplication: %.1f + %.1fi\n", e.re, e.im);
    printf("Addition: %.1f + %.1fi\n", f.re, f.im);
    printf("Subtraction: %.1f + %.1fi\n", g.re, g.im);
    return 0;
}