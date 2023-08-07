void foo(int *a)
{
    a[3] = -1;
    a[2] = 0;
    a[1] = 1;
    a[0] = 0;
}

void mirror(int a[4][6])
{
    int i, j, temp;
    for (i = 0; i < 4; i=i+1)
    {
        for (j = 0; j < 3; j=j+1)
        {
            temp = a[i][j];
            a[i][j] = a[i][5-j];
            a[i][5-j] = temp;
        }
    }
}


int main()
{
    int a[2][4][6], **b;
    int i, j, k;
    for(i = 0; i < 2; i=i+1)
    {
        for(j = 0; j < 4; j=j+1)
        {
            for (k = 0; k < 6; k=k+1)
            {
                a[i][j][k] = i+j+k;
            }
        }
    }
    for (i = 0; i < 2; i=i+1)
    {
        printf("Row %d:\n", i);
        for (j = 0; j < 4; j=j+1)
        {
            for (k = 0; k < 6; k=k+1)
            {
                printf("%d ", a[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    foo(a[1][3]);
    printf("Foo:\n");
    for (i = 0; i < 2; i=i+1)
    {
        printf("Row %d:\n", i);
        for (j = 0; j < 4; j=j+1)
        {
            for (k = 0; k < 6; k=k+1)
            {
                printf("%d ", a[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    mirror(a[0]);
    printf("Mirror:\n");
    for (i = 0; i < 2; i=i+1)
    {
        printf("Row %d:\n", i);
        for (j = 0; j < 4; j=j+1)
        {
            for (k = 0; k < 6; k=k+1)
            {
                printf("%d ", a[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
