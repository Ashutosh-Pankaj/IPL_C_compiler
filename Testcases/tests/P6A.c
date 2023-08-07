int foo(int *a)
{
    a[0] = 2;
    printf("%d\n", a[0]);
    return 0;
}

int main()
{
    int a[10];
    int i;
    for(i = 0; i < 10; i=i+1)
    {
        a[i] = i;
    }
    printf("%d\n", foo(a));
    return 0;
}
