int main() {
  int x, *ptr;
  x = 10;
  ptr = &x;
  
  printf("The value of x is: %d\n", x);
  /* printf("The value of ptr is: %p\n", ptr); */
  printf("The value that ptr points to is: %d\n", *ptr);
  
  *ptr = 20;
  
  printf("After changing the value that ptr points to, the value of x is: %d\n", x);
  
  return 0;
}
