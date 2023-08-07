int foo(int *a, int num)
{
    printf("Foo:\n");
    printf("%d ", a[0]);
    printf("%d ", a[1]);
    printf("%d ", a[2]);
    a[0] = num;
    printf("%d\n", a[0]);
    return 0;
}

int main()
{
    int a[10], *p;
    int i;
    for(i = 0; i < 10; i=i+1)
    {
        a[i] = i;
    }
    printf("%d\n", foo(a+4, 44));
    printf("%d\n", foo(a+3, 23));
    p = a + 1;
    printf("%d\n", foo(p+1, 17));
    printf("%d\n", foo(a+1, 85));
    printf("%d\n", foo(p-1, 99));
    return 0;
}
