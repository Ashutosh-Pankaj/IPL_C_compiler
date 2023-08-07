
int main() {
    int start, end, sum, i;

    start = 1;
    end = 100;
    sum = 0;

    if (start > end) {
        printf("Invalid input. Please ensure that the starting number is less than or equal to the ending number.\n");
    } else {
        for (i = start; i <= end; i = i+1) {
            if (i / 2 == (i + 1) / 2) {
                sum = sum + i;
                printf("Intermediate sum : %d\n", sum);
            }
            else ;
        }
        printf("The sum of all even numbers between %d and %d is: %d\n", start, end, sum);
    }

    return 0;
}
