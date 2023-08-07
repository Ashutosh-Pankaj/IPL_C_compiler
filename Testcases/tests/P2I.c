int main() {
    int multiple, start, end, sum, i;

    sum = 0;
    multiple = 10;
    start = 1;
    end = 100;

    if (start > end || multiple <= 0) {
        printf("Invalid input. Please enter a positive multiple and ensure that the starting number is less than or equal to the ending number.\n");
    } else {
        for (i = start; i <= end; i = i +1) {
            if (i / multiple * multiple == i) {
                sum = sum + i;
                printf("Intermediate sum : %d\n", sum);
            }
            else ;
        }
        printf("The sum of all multiples of %d between %d and %d is: %d\n", multiple, start, end, sum);
    }

    return 0;
}
