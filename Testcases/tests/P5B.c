void swap(int *a, int *b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  int x, y;
  x = 10;
  y = 20;
  printf("Before swapping, x = %d and y = %d\n", x, y);
  
  swap(&x, &y);
  
  printf("After swapping, x = %d and y = %d\n", x, y);
  
  return 0;
}
