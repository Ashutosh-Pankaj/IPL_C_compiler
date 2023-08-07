int main() {
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
    int node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node14;
    int result;

    a = 10;
    b = 20;
    c = 30;
    d = 40;
    e = 50;
    f = 60;
    g = 70;
    h = 80;
    i = 90;
    j = 100;
    k = 110;
    l = 120;
    m = 130;
    n = 140;
    o = 150;
    p = 160;
    q = 170;
    r = 180;
    s = 190;
    t = 200;
    u = 210;
    v = 220;
    w = 230;
    x = 240;
    y = 250;
    z = 260;
    
    node1 = a + b;
    node2 = c - d;
    node3 = e * f;
    node4 = g / h;
    node5 = i >= j;
    node6 = k <= l;
    node7 = m > n;
    node8 = o < p;
    node9 = q == r;
    node10 = s != t;
    node11 = !u;
    node12 = -v;
    node13 = w && x;
    node14 = y || z;

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
    
    result = node1 + node2 - node3 * node4 / (node5 + 1) + node6 * node7 - node8 / (node9 + 1) - node10;
    printf("Result: %d\n", result);

    result = result + !node11;
    printf("Result: %d\n", result);

    result = result && !node12;
    printf("Result: %d\n", result);

    result = result || node13 && node14;
    printf("Result: %d\n", result);

    result = ((a + b) + (c - d) - (e * f) * (g / h) / ((i >= j) + 1)) + ((k <= l) * (m > n) - (o < p) / ((q== r) + 1) - (s != t));
    printf("Result: %d\n", result);
    
    return 0;
}
