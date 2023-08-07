int f(int x) {
    x = 4;
    return x + 1;
}

int main() {
    int x;
    x = 1;
    printf("%d %d %d\n", x, f(x), x);
    return 0;
}
