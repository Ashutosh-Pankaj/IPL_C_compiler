int main() {
    int a, b, c, d, e;

    a = 10;
    d = (a > 5);
    b = a - d;
    c = (b > 0);
    e = a + b + c;

    printf("a = %d, b = %d, c = %d, d = %d, e = %d\n", a, b, c, d, e);
    printf("b > 0 is %d\n", b > 0);
    printf("a - d is %d\n", a - d);
    printf("e - 1 is %d\n", e - 1);
    printf("c * d is %d\n", c * d);

    return 0;
}