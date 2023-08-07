int g(int x,int y)
{
 return y-x;
}
int f(int x,int y)
{
 return x+y;
}
int main()
{
 int a,b,c,i,sum;
 sum = 0;
 a=1;
 b=1;
 c=0;
 while(c==0)
 {
  for(i=g(a,b);i<=f(a,b);i=i+1)
  {
   sum=sum+i;
  }
  if(sum>100)
  {
   c=1;
  }
  else
  {
   a=a*5;
   b=b*5;
  }
 }
 printf("%d\n",sum);
 return 0;
}
