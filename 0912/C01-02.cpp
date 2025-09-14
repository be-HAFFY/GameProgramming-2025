/* 구구단 3단 출력하기 */

#include <stdio.h>
#include <windows.h>
void gotoxy(int x, int y);

int main(void){
    for(int i = 1; i <= 9 ; i++){
        gotoxy(35, 5+i);
        printf("%d*%d=%2d", 3, i, 3*i);
    }
    printf("\n");
    return 0;
}

void gotoxy(int x, int y){
    COORD Pos = {(SHORT)(x-1), (SHORT)(y-1)}; //COORD 구조체는 SHORT로 정의되어 있음.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
