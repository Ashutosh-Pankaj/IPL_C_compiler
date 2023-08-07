int main() {
    int a, b, c, d, e, f, g;
    a = 10;
    b = 15;
    c = 5;
    d = 3;
    e = 4;
    f = 8;
    g = 9;

    printf("Before assignment: a = %d, b = %d, c = %d, d = %d, e = %d, f = %d, g = %d\n", a, b, c, d, e, f, g);

    b = (a - c) * (a - c + 1);
    a = b + c - 5;
    c = (b > a) && (b < 50);
    d = (a == b) || (c != a);
    e = (c && d) || ((a + b + c + d) == (a - b) * c - d);
    f = (a + b) / (c - 1);
    g = d * (-e);

    printf("After assignment: a = %d, b = %d, c = %d, d = %d, e = %d, f = %d, g = %d\n", a, b, c, d, e, f, g);

    return 0;
}
