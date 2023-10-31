// main3.c (./static/main3.c)
#include <stdio.h>
#include "../sub/calc.h"

int main() {
    int a = 10;
    int b = 5;

    printf("%d\n", add(a, b));
    printf("%d\n", sub(a, b));
    printf("%d\n", div(a, b));
    printf("%d\n", mul(a, b));

    return 0;
}
