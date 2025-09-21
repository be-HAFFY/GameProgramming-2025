#include <stdio.h>
#include <stdlib.h>

void push(char data);
char pop(void);
struct stack_node{
    char data;
    struct stack_node *link;
};

struct stack_node *top = NULL; // 스택의 top 포인터 선언 및 초기화

int main(void){
    // 예시: 스택에 데이터 넣고 빼기
    push('A');
    push('B');
    printf("%c\n", pop()); // B 출력
    printf("%c\n", pop()); // A 출력

    return 0;
}

void push(char data){
    struct stack_node *new_node;
    new_node = (struct stack_node*)malloc(sizeof(struct stack_node));
    new_node -> data = data;
    new_node -> link = top;
    top = new_node;
}

char pop(void){
    struct stack_node *temp;
    char data;
    if(top == NULL) {
        printf("empty\n");
        return '\0'; // 스택이 비었을 때 널 문자 반환
    }
    data = top -> data;
    temp = top;
    top = top -> link;
    free(temp); // 메모리 해제
    return data;
}