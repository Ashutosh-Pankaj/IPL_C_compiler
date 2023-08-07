
int main() {
    int start, end, sum, i;

    start = 1;
    end = 100;
    sum = 0;


    if (start > end) {
        printf("Invalid input. Please ensure that the starting number is less than or equal to the ending number.\n");
    } else {
        i = start;
        while (i <= end) {
            if (i / 2 != (i + 1) / 2) {
                sum = sum + i;
                printf("Intermediate sum : %d\n", sum);
            }
            else ;
            i = i + 1;
        }
        printf("The sum of all odd numbers between %d and %d is: %d\n", start, end, sum);
    }

    return 0;
}
