int main() {
    int a, b, c, d, e, f, g;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    e = 5;
    f = 6;
    g = 7;

    printf("Before assignment: a = %d, b = %d, c = %d, d = %d, e = %d, f = %d, g = %d\n", a, b, c, d, e, f, g);

    /* First level of the tree */
    a = b + c;
    b = d - e;
    c = f * g;
    d = c / a;

    /* Second level of the tree */
    e = a + b;
    f = c - d;

    /* Third level of the tree */
    g = e * f;

    /* Fourth level of the tree */
    a = g - d;
    b = e + f;
    c = a * b;

    printf("After assignment: a = %d, b = %d, c = %d, d = %d, e = %d, f = %d, g = %d\n", a, b, c, d, e, f, g);

    return 0;
}
