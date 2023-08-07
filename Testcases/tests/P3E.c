/* pass by value check */
void unmodify(int a) {
    a = 2;
}

int main () {
    int a;
    a = 1;
    printf("a = %d\n", a);
    unmodify(a);
    printf("a = %d\n", a);
    return 0;
}
