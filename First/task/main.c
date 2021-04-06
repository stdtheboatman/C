#include <stdio.h>
#include <limits.h>

const int intMax = INT_MAX;


int main() {
    printf("Max int is %i\n", intMax);

    int fib[1024];

    fib[0] = 1;
    fib[1] = 1;

    int index = 2;
    while(1LL * fib[index - 1] + fib[index - 2] <= intMax) {
        fib[index] = fib[index - 1] + fib[index - 2];
        index++;
    }

    printf("Max int fib is %i\n", fib[index - 1]);

    int sum = 0;
    for(int i = 0; i < index; i++) {
        if (1LL * sum + fib[i] <= intMax) {
            sum += fib[i];
        }
        else {
            break;
        }
    }

    printf("Max int sum fib is %i\n", sum);

    return 0;
}
