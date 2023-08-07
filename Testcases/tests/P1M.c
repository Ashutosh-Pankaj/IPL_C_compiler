int main() {

	int x, y, z, u, w, a, b, c;

	x = 10;
	y = x + 9;
	z = y - 8;
	u = z + 7;
	w = u - 6;
	a = w + 5;
	b = a - 4;
	c = b + 3; 

	printf("%d %d %d\n", x+c-w, z*a, a+b+c - x+y+z);

	return 0;
}