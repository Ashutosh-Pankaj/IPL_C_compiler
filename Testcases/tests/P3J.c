/* larger recursion */
int recurse(int d, int n) {
    if (d <= 0) {
        return n;
    }

    else {
        printf("At depth %d : n = %d\n", d, n);
        
        return (recurse(d - 1, n + d) + recurse(d - 2, n - d));
    }
}



int main() {
    int a, b;
    a = recurse(2, 2);
    printf("a = %d\n", a);
    b = recurse(a, 1);
    printf("b = %d\n", b);
    a = recurse(a, b);
    printf("a = %d\n", a);
    return 0;
} 

