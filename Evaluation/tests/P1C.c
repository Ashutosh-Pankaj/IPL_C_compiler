int main() {
	
	int x, y, z, u, w;

	x = 0;
	w = (x >= 0);
	y = x - w;
	u = (y > 0);
	z = x + y + u;

	printf("%d %d %d\n", 1+x, z-1, -u-w+y*y);

	return 0;
}