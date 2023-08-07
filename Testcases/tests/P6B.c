void foo(int a[4][4])
{
    a[3][3] = -1;
    a[2][2] = 0;
    a[1][1] = 1;
    a[0][0] = 0;
}


int main()
{
    int a[4][4], **b;
    int i, j;
    for(i = 0; i < 4; i=i+1)
    {
        for(j = 0; j < 4; j=j+1)
        {
            a[i][j] = i+j;
        }
    }
    for(i = 0; i < 4; i=i+1)
    {
        for(j = 0; j < 4; j=j+1)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("Foo:\n");
    foo(a);
    for(i = 0; i < 4; i=i+1)
    {
        for(j = 0; j < 4; j=j+1)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
