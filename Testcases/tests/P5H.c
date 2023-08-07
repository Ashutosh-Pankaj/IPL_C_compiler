struct Point {
  int x;
  int y;
};

void print_points(struct Point *points_ptr, int num_points) {
  int i;
  for (i = 0; i < num_points; i=i+1) {
    if (points_ptr->x > 0 && points_ptr->y > 0) {
      printf("(%d, %d) is in the first quadrant\n", points_ptr->x, points_ptr->y);
    } else {
      printf("(%d, %d) is not in the first quadrant\n", points_ptr->x, points_ptr->y);
    }
    points_ptr = points_ptr - 1;
  }
}

int main() {
  struct Point p1, p2, p3, p4, *points_ptr;
  p1.x = 1;
  p1.y = 2;

  p2.x = -1;
  p2.y = 2;

  p3.x = 1;
  p3.y = -2;

  p4.x = -1;
  p4.y = -2;
  
  points_ptr = &p1;
  
  print_points(points_ptr, 4);
  
  return 0;
}
