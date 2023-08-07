int main() {
    int a, b, c, d;
    int node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node14;
    int result;

    a = 10;
    b = 20;
    c = 30;
    d = 40;
    node1 = a + b;
    node2 = c - d;
    node3 = node1 * node2;
    node4 = node1 / node2;
    node5 = node1 > node2;
    node6 = node1 < node2;
    node7 = node1 >= node2;
    node8 = node1 <= node2;
    node9 = node1 == node2;
    node10 = node1 != node2;
    node11 = -node1;
    node12 = !node2;
    node13 = node1 && node2;
    node14 = node1 || node2;

    printf("Node1: %d\n", node1);
    printf("Node2: %d\n", node2);
    printf("Node3: %d\n", node3);
    printf("Node4: %d\n", node4);
    printf("Node5: %d\n", node5);
    printf("Node6: %d\n", node6);
    printf("Node7: %d\n", node7);
    printf("Node8: %d\n", node8);
    printf("Node9: %d\n", node9);
    printf("Node10: %d\n", node10);
    printf("Node11: %d\n", node11);
    printf("Node12: %d\n", node12);
    printf("Node13: %d\n", node13);
    printf("Node14: %d\n", node14);
    
    result = node3 + node4 - node5 * node6 / (node7 + 1) - node8 + node9 * node10 - node11 / (node12 + 1);
    printf("Result: %d\n", result);

    result = result + !node13;
    printf("Result: %d\n", result);

    result = result && !node14;
    printf("Result: %d\n", result);

    result = ((node1 * node2) + (node1 / node2) - (node1 > node2) * (node1 < node2) / ((node1 >= node2) + 1) - (node1 <= node2)) + ((node1 == node2) * (node1 != node2) - (-node1) / ((!node2) + 1));
    printf("Result: %d\n", result);

    result = (((a+b) * (c-d)) + ((a+b) / (c-d)) - ((a+b) > (c-d)) * ((a+b) < (c-d)) / (((a+b) >= (c-d)) + 1) - ((a+b) <= (c-d))) + (((a+b) == (c-d)) * ((a+b) != (c-d)) - (-(a+b)) / ((!(c-d)) + 1));
    printf("Result: %d\n", result);

    return 0;
}
