int main() {
    int a, b, c;
    int node1, node2, node3, node4, node5, node6, node7, node8, node9, node10;

    a = 10;
    b = 15;
    c = 5;

    printf("a = %d, b = %d, c = %d\n", a, b, c);

    node1 = a - c;
    node2 = node1 + 1;
    node3 = node1 * node2;
    b = node3;
    
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    node4 = b + c;
    node5 = node4 - 5;
    a = node5;
    
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    node6 = b > a;
    node7 = b < 50;
    c = node6 && node7;

    printf("a = %d, b = %d, c = %d\n", a, b, c);

    node8 = a * a;
    node9 = b * b;
    node10 = c * c;

    printf("a = %d, b = %d, c = %d\n", a, b, c);
    printf("%d\n", node8 - node9 + node10);

    return 0;
}
