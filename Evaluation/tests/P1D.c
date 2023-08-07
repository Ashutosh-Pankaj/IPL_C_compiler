int main() {

	int a, b, c;

	a = 10;
	b = 15;
	c = 5;

	b = (a - c) * (a - c + 1);
	a = b + c - 5;
	c = (b > a) && (b < 50);

	printf("%d\n", a*a - b*b + c*c);

	return 0;
}