// main.c
#include <stdio.h>

// 정적 라이브러리의 함수 선언을 포함합니다.
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int main() {
    int num1 = 10, num2 = 5;
    printf("덧셈 결과: %d\n", add(num1, num2));
    printf("뺄셈 결과: %d\n", sub(num1, num2));
    printf("곱셈 결과: %d\n", mul(num1, num2));
    printf("나눗셈 결과: %d\n", div(num1, num2));

    return 0;
}