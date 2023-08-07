int main()
{
  int i;
  int j;
  int prod;
  prod=1;
  for(i=1;i<5;i=i+1)
  {
    for(j=1;j<5;j=j+1)
    {
        prod = i*j;
        printf("%d\n",prod);
    }
  }

  return 0;
}
