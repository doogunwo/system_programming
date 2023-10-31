// main1.c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    void* handle = dlopen("../sub/libtest.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "라이브러리를 열 수 없습니다: %s\n", dlerror());
        return 1;
    }

    int a = 10;
    int b = 5;

    // 함수 포인터를 가져와서 함수 호출
    int (*add_function)(int, int) = dlsym(handle, "add");
    int (*sub_function)(int, int) = dlsym(handle, "sub");
    int (*mul_function)(int, int) = dlsym(handle, "mul");
    int (*div_function)(int, int) = dlsym(handle, "div");

    int result_add = add_function(a, b);
    int result_sub = sub_function(a, b);
    int result_mul = mul_function(a, b);
    int result_div = div_function(a, b);

    printf("Add: %d\n", result_add);
    printf("Subtract: %d\n", result_sub);
    printf("Multiply: %d\n", result_mul);
    printf("Divide: %d\n", result_div);

    dlclose(handle);
    return 0;
}

