#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex {
    double re, im;
    double (*abs)(struct Complex *this);
    struct Complex (*add)(struct Complex *this, struct Complex *other);
    struct Complex (*sub)(struct Complex *this, struct Complex *other);
    struct Complex (*mul)(struct Complex *this, struct Complex *other);
    struct Complex (*sqr)(struct Complex *this);
};
extern const struct ComplexClass {
    struct Complex (*new)(double real, double imag);
} Complex;



#endif // COMPLEX_H