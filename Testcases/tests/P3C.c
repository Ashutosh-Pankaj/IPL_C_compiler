/* recursion */
int f(int x)
{
 if(x==0)
 {
    return 1;
 }
 else ;
 return x*f(x-1);
}
int main()
{
 int x;
 x=10;
 printf("%d\n",f(x));
 return 0;
}
