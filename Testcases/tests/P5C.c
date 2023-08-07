void print_numbers(int *start_ptr, int num_elements) {
  int i;
  i = 0;
  while (i < num_elements) {
    if (*start_ptr / 2 * 2 == *start_ptr) {
      printf("%d is even\n", *start_ptr);
    } else {
      printf("%d is odd\n", *start_ptr);
    }
    
    start_ptr = start_ptr - 1;
    i = i + 1;
  }
}

int main() {
  int x, y, *ptr1, *ptr2;
  x = 10;
  y = 20;
  ptr1 = &x;
  ptr2 = &y;
  
  print_numbers(ptr1, 2);
  
  ptr1 = ptr1 - 1;
  *ptr1 = 15;
  
  print_numbers(&x, 2);
  return 0;
}
