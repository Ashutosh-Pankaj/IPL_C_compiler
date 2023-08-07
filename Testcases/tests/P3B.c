/* simple function */
int f(int x,int y)
{
 return x+y;
}

int main()
{
 int x,y;
 x=10;
 y=20;
 while(f(x,y)<100)
 {
  x=x*2;
  y=y*5;
 }
 printf("%d\n",f(x,y));
 return 0;
} 
