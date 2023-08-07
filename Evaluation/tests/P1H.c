int main() {
	
	int x, y;

	x = 17;
	y = x - 2;
	y = x * y - y * y;

	printf("%d %d\n", x-5, -y+x);

	return 0;
}