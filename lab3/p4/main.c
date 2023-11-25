#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SENTENCE_LENGTH 1000
double timestamp(clock_t start, clock_t end, int current_char);

int main(){
    char sentence[MAX_SENTENCE_LENGTH];
    char user_input[MAX_SENTENCE_LENGTH];
    clock_t start, end;
    int correct_characters = 0;

    printf("타자 연습을 시작합니다. 다음 문장을 입력하세요:\n");
    printf("The quick brown fox jumps over the lazy dog.\n");

    fgets(user_input, MAX_SENTENCE_LENGTH, stdin);

    start = clock();

    for (int i = 0; i < strlen(user_input); i++) {
        if (user_input[i] == "The quick brown fox jumps over the lazy dog."[i]) {
            correct_characters++;
        }
    }

    end = clock();

    double records = timestamp(start,end,correct_characters);
    printf("올바르게 입력된 문자 수: %d\n", correct_characters);
    printf("틀린 문자 수: %ld\n",strlen(user_input)-correct_characters);
    printf("평균 분당 타자 수: %.2f\n", records);

    return 0;
}

double timestamp(clock_t start, clock_t end, int correct_characters){
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    double typing_speed = (correct_characters / 5.0) / (elapsed_time / 60.0); // 5.0은 단어당 평균 글자 수입니다.
    return typing_speed;
}