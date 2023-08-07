int g(int x,int y)
{
 return x*y;
}
int f(int x,int y)
{
 return x+y;
}
int main()
{
 int a,b,x;
 a=10;
 b=1;
 x=(f(a,b)>10) && (g(a,b)<=10);
 printf("%d\n",x);
 return 0;
}
