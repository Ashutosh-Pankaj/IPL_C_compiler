
int main() {
    int side1, side2, side3;

    side1 = 10;
    side2 = 5;
    side3 = 7;

    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        printf("Invalid side length. Please enter positive values.\n");
    } else if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
        if (side1 == side2 && side2 == side3) {
            printf("The triangle is equilateral.\n");
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            printf("The triangle is isosceles.\n");
        } else {
            printf("The triangle is scalene.\n");
        }
    } else {
        printf("The given side lengths do not form a valid triangle.\n");
    }

    return 0;
}
