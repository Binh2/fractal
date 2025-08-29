#include "Complex.h"
#include <math.h>
#include <stdlib.h>

static double complex_abs(struct Complex *this) {
    return sqrt(this->re*this->re + this->im*this->im);
}
static struct Complex complex_add(struct Complex *this, struct Complex *other) {
    return (struct Complex){.re=this->re+other->re, .im=this->im+other->im};
}
static struct Complex complex_sub(struct Complex *this, struct Complex *other) {
    return (struct Complex){.re=this->re-other->re, .im=this->im-other->im};
}
static struct Complex complex_mul(struct Complex *this, struct Complex *other) {
    return (struct Complex){.re=this->re*other->re - this->im*other->im, .im=this->re*other->im + this->im*other->re};
}
static struct Complex complex_sqr(struct Complex *this) {
    return (struct Complex){.re=this->re*this->re, .im=this->im*this->im };
}

static struct Complex new(double real, double imag) {
    return (struct Complex){.re=real, .im=imag, .abs=&complex_abs, 
        .add=&complex_add, .sub=&complex_sub, .mul=&complex_mul, .sqr=&complex_sqr};
}
const struct ComplexClass Complex={.new=&new};

	