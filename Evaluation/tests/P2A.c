int main()
{
  int i, j;
  i=1;
  while (i<=10)
  {
    for(j=1;j<=i;j=j+1)
    {
      if(j / 2 * 2 == j)
      {
        printf("Even");
      }
      else
      {
        printf("Odd");
      }
    }
    printf("\n");
    i=i+1;
  }

  return 0;
}
