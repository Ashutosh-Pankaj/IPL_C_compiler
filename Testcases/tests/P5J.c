int func1(int *a){
  int temp, b;
  temp = *a+10;
  if(*a < 10)
    b = 10;
  else
    b = 2;
  *a = *a * (b + temp);
  return b;
}
int main(){
  int a, b;
  a = 9;
  b = 0;
  printf("Before func1: %d %d\n",a,b);
  b = func1(&a);
  printf("After first call func1: %d %d\n",a,b);
  b = func1(&a);
  printf("After second call func1: %d %d\n",a,b);
  return 0;
}
