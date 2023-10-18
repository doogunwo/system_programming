// main2.c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    
    void *lib = dlopen("./calc.so", RTLD_LAZY);
    if (!lib) {
        fprintf(stderr, "라이브러리를 열 수 없습니다: %s\n", dlerror());
        return 1;
    }
    int (*add)(int, int) = dlsym(lib, "add");
    int (*sub)(int, int) = dlsym(lib, "sub");
    int (*mul)(int, int) = dlsym(lib, "mul");
    int (*div)(int, int) = dlsym(lib, "div");

    int num1 = 10, num2 = 5;

    printf("덧셈 결과: %d\n", add(num1, num2));
    printf("뺄셈 결과: %d\n", sub(num1, num2));
    printf("곱셈 결과: %d\n", mul(num1, num2));
    printf("나눗셈 결과: %d\n", div(num1, num2));

    dlclose(lib);
    return 0;

}
