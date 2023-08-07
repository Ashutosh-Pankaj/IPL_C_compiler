/* larger AR */

int final (int a) {
    printf("final: %d\n", a);
    return a + 100;
}

int i(int a) {
    printf("i: %d\n", a);
    return final(a + a * 100);
}

int h(int a, int b) {
    printf("h: %d %d\n", a, b);
    return i(a - b);
}

int g(int a, int b) {
    printf("g: %d %d\n", a, b);
    return h(a++, b+1);
}

int f(int a) {
    printf("f: %d\n", a);
    return g(a, 2 * a);
}

int main () {
    printf("main: %d %d\n", 1, f(1));
    return 0;
}
