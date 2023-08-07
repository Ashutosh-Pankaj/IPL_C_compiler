void foo(int a[20][20])
{
    int i,ii;
    for(i=10;i>0;i=i-1)
    {
        for(ii=20;ii>0;ii=ii-1)
        {
            a[i][ii] = 11*ii;
        }
    }
    for (i=10;i>0;i=i-1)
    {
        for(ii=20;ii>0;ii=ii-1)
        {
            printf("%d ",a[i][ii]);
        }
        printf("\n");
    }
}
int main()
{
    int a[30][20], i, ii;
    for(i=10;i>0;i=i-1)
    {
        for(ii=20;ii>0;ii=ii-1)
        {
            a[i][ii] = 10*i-21+ii;
            printf("%d ",a[i][ii]);
        }
        printf("\n");
    }
    foo(a);
    for(i=10;i>0;i=i-1)
    {
        for(ii=20;ii>0;ii=ii-1)
        {
            printf("%d ",a[i][ii]);
        }
        printf("\n");
    }
    return 0;
}
