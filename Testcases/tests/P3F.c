int f(int x,int y)
{
 return x+y;
}

int g(int x,int y)
{
 return x+y;
}

int main()
{
 int a,b,c,d;
 a=10;
 b=20;
 c=5;
 d=100;
 if(f(a,b)==g(c,d))
 {
  printf("equal\n");
 }
 else
 {
  printf("not equal\n");
 }
 return 0;
}
