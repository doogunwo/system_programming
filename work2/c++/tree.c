/*

학생 수를 입력받은 다음, 학생의 이름, 중간, 기말 점수를 기록하는 구조체를
학생 수만큼 동적으로 할당받아서, 이를 트리 구조체로 활용하여 트리 탐색을 할 수 있는 프로그램을 작성하시오.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record{
    char name[20];
    int midterm;
    int final;
    struct record *left;
    struct record *right;  
};

struct record *insert_record(struct record *root,char name[20],int midterm, int final){
    if(root == NULL){
        struct record *newRecord = (struct record *)malloc(sizeof(struct record));
        strncpy(newRecord->name, name, 20);
        newRecord->midterm = midterm;
        newRecord->final = final;
        newRecord->left = NULL;
        newRecord->right = NULL;
        return newRecord;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insert_record(root->left, name, midterm, final);
    } else {
        root->right = insert_record(root->right, name, midterm, final);
    }

    return root;
}

void printRecord(struct record *root) {
    if (root != NULL) {
        printRecord(root->left);
        printf("Name: %s, Midterm Score: %d, Final Score: %d\n", root->name, root->midterm, root->final);
        printRecord(root->right);
    }
}

void freeStudentTree(struct record *root) {
    if (root != NULL) {
        freeStudentTree(root->left);
        freeStudentTree(root->right);
        free(root);
    }
}


int main(){
    int num = 0;
    printf("Enter the number of students: ");
    scanf("%d",&num);

    struct record  *root = NULL;

     for (int i = 0; i < num; i++) {
        char name[50];
        int midTermScore, finalScore;
        printf("Enter student name: ");
        scanf("%s", name);
        printf("Enter midterm score: ");
        scanf("%d", &midTermScore);
        printf("Enter final score: ");
        scanf("%d", &finalScore);

        root = insert_record(root, name, midTermScore, finalScore);
    }

    printf("Student Information (In-order traversal):\n");
    printRecord(root);

    // 메모리 해제
    freeStudentTree(root);

    return 0;

}

