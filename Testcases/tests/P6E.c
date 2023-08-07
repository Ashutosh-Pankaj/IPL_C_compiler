int main()
{
    int i, j, a[30][30], b[10], c[20];


    for(i=10; i<20;i=i+1)
    {
       b[i] = i-10;
       printf("\nb: %d, %d",i,b[i]);
    }

    for(i=40; i>20; i=i-1)
    {
       c[i] = i-21;
       printf("\nc: %d, %d",i,c[i]);

    }

    for(i=40; i>20; i=i-1)
    {
       printf("\nC: %d",c[i]);
    }

    for(i=10; i<20;i=i+1)
    {
       printf("\n%d: B:",i);
       printf("%d", b[i]); 
    }

    for(i=0; i<10;i=i+1)
    {
        for(j=0; j<20;j=j+1)
        {
            a[i][j] = i*j+1;
        }
    }

    for(i=0; i<10;i=i+1)
    {
        for(j=0; j<20;j=j+1)
        {
            printf("\n%d",a[b[i+10]][c[j+21]]);
        }
    }

    return 0;
}