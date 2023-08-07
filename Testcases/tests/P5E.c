struct Rectangle {
  int length;
  int width;
};

int area(struct Rectangle *rect_ptr) {
  return rect_ptr->length * rect_ptr->width;
}

int main() {
  struct Rectangle r1, *rect_ptr;
  r1.length = 5;
  r1.width = 10;
  rect_ptr = &r1;

  while (rect_ptr != 0) {
    printf("Area of rectangle with length %d and width %d is %d\n", rect_ptr->length, rect_ptr->width, area(rect_ptr));
    rect_ptr = 0;
 }
  return 0;
}

