/* same param name and function name */

int a(int a) {
    printf("%d\n", a);
    return a + 1;
}

int main () {
    int q;
    q = 1;
    printf("%d\n", a(a(a(a(q)))));
    return 0;
}
