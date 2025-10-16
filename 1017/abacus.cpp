#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

// 주판 프로그램 기본 기능
void draw_rectangle(int c, int r);
void display_abacus(int m[]);
void div_number(int mc[], long number);
void gotoxy(int x, int y);

// 프로그램 추가 기능
void basic_calculator();
void abacus_speed_game();
void save_leaderboard(const char* filename, const char* username, double elapsed);
void display_leaderboard(const char* filename);
int compare_records(const void *a, const void *b);
void countdown();

// 점수 기록용 구조체
typedef struct {
    char name[50];
    double time;
} Record;

int main(void)
{
    int choice;
    system("cls");
    
    while (1)
    {
        // 메인 화면 출력
        system("cls");
        draw_rectangle(30, 9);
        gotoxy(5, 2); printf("=== 주판 프로그램 ===");
        gotoxy(5, 4); printf("1. 기본 계산기능");
        gotoxy(5, 5); printf("2. 주판 빠르게 읽기 게임");
        gotoxy(5, 7); printf("프로그램 종료(ESC)");
        gotoxy(5, 8); printf("입력 > ");

        // 키 입력
        choice = _getch();
        if (choice == 27) break; // ESC 눌렀을 때 종료

        switch (choice)
        {
            case '1':
                basic_calculator();
                break;
            case '2':
                abacus_speed_game();
                break;
            default:
                gotoxy(5, 10); printf("잘못된 입력입니다.");
                Sleep(1000);
                gotoxy(5, 10); printf("                  ");
        }
    }

    gotoxy(5, 10); printf("프로그램을 종료합니다...");
    Sleep(1000);
    gotoxy(5, 10); printf("                        ");
    system("cls");
    return 0;
}

// ================== 기본 계산기 기능 ===================
void basic_calculator()
{
    long number = 0, InputNumber = 0;
    int mc[9];
    system("cls");
    div_number(mc, number);
    gotoxy(1, 5);
    draw_rectangle(20, 8);
    gotoxy(1, 4);
    printf("  ");
    for (int i = 0; i <= 8; i++)
        printf("%2d", mc[i]);
    display_abacus(mc);

    gotoxy(1, 1);
    printf("기본 계산기 기능입니다. (r: 돌아가기)\n");

    while (1)
    {
        gotoxy(1, 2);
        printf("(양수: 더하기, 음수: 빼기, 0: 초기화)\n");
        gotoxy(1, 16);
        printf("                                                                   ");
        gotoxy(1, 16);
        printf("9자리 내 숫자 입력 > ");
        fflush(stdin);

        char buf[20];
        fgets(buf, sizeof(buf), stdin);  // 문자열로 입력 받음

        if (buf[0] == 'r' || buf[0] == 'R')  // r 또는 R 입력 시 돌아가기
            break;

        long InputNumber = strtol(buf, NULL, 10);  // 문자열 -> 숫자

        if (InputNumber == 0) number = 0; // 초기화
        else number += InputNumber;

        if (number > 999999999 || number < 0)
        {
            gotoxy(1, 18); printf("계산 범위를 초과했습니다.\n");
            Sleep(1000);
            number -= InputNumber; // 되돌리기
            gotoxy(1, 18); printf("                          ");
            continue;
        }

        div_number(mc, number);
        gotoxy(1, 4);
        printf("  ");
        for (int i = 0; i <= 8; i++)
            printf("%2d", mc[i]);
        display_abacus(mc);
    }
}

// ================== 주판 빠르게 읽기 게임 기능 ===================
void abacus_speed_game()
{
    int choice;
    system("cls");
    gotoxy(1,1);
    printf("주판 빠르게 읽기 게임\n");
    gotoxy(1,2);
    printf("1. 게임 시작\n2. 리더보드 확인\nr. 돌아가기\n");

    while (1)
    {
        choice = _getch();
        if (choice == '1') break;      // 게임 시작
        else if (choice == '2')        // 리더보드 확인
        {
            system("cls");
            display_leaderboard("leaderboard.txt");
            printf("아무 키나 누르면 돌아갑니다.\n");
            _getch();
            system("cls");
            gotoxy(1,1);
            printf("주판 빠르게 읽기 게임\n");
            gotoxy(1,2);
            printf("1. 게임 시작\n2. 리더보드 확인\nr. 돌아가기\n");
        }
        else if (choice == 'r' || choice == 'R') return; // 돌아가기
    }

    // ========== 게임 시작 ==========
    long numbers[9]; // 1~9자리 숫자
    int mc[9];
    srand((unsigned)time(NULL));

    // 무작위로 1~9자리 숫자 생성
    for (int i = 0; i < 9; i++)
    {
        int len = i + 1;
        long num = 0;
        for (int j = 0; j < len; j++)
            num = num * 10 + (rand() % 10);
        numbers[i] = num;
    }

    system("cls");
    printf("3초 후 게임을 시작합니다...\n");
    printf("화면에 그려진 주판을 보고 숫자를 입력하세요.\n");
    printf("총 9번 진행됩니다.\n");
    Sleep(3000);
    countdown();

    clock_t start = clock(); // 시작 시간 측정

    for (int i = 0; i < 9; i++)
    {   
        printf("남은 문제 : %d/9\n", i);
        printf("r. 돌아가기\n");
        div_number(mc, numbers[i]);
        display_abacus(mc);

        while (1) // 정답 입력할 때까지 반복
        {
            char buf[20];
            gotoxy(1,16);
            printf("숫자 입력 > ");
            fgets(buf, sizeof(buf), stdin);

            if (buf[0] == 'r' || buf[0] == 'R') return; // 돌아가기

            long userInput = strtol(buf, NULL, 10);

            if (userInput == numbers[i]){
                system("cls");
                break; // 정답이면 다음 숫자로
            }
            else{
                gotoxy(1,16);
                printf("                                      ");
                gotoxy(1,16);
                printf("숫자를 입력 > ");
                gotoxy(1,17);
                printf("틀렸습니다! 잠시 후 다시 시도하세요.\n");
                Sleep(1000); // 1초 표시 후 입력 대기
                gotoxy(1,17);
                printf("                                      ");
            }
        }
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    // 사용자 이름 입력
    char username[50];
    gotoxy(1,1);
    printf("게임 종료! 걸린 시간: %.2f초\n", elapsed);
    printf("사용자 이름 입력 > ");
    fgets(username, sizeof(username), stdin);
    char *p = strchr(username, '\n'); // 개행 제거
    if (p) *p = '\0';

    // 리더보드 저장
    save_leaderboard("leaderboard.txt", username, elapsed);

    printf("리더보드에 기록되었습니다.\n아무 키나 누르면 메인 화면으로 돌아갑니다.\n");
    _getch();
}

void save_leaderboard(const char* filename, const char* username, double elapsed)
{
    FILE *fp = fopen(filename, "a");
    if (fp)
    {
        fprintf(fp, "%s: %.2f\n", username, elapsed);
        fclose(fp);
    }
}

void display_leaderboard(const char* filename)
{
    Record records[100];
    int count = 0;

    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        while (fscanf(fp, "%49[^:]: %lf\n", records[count].name, &records[count].time) == 2)
            count++;
        fclose(fp);

        // 시간 기준 오름차순 정렬
        qsort(records, count, sizeof(Record), compare_records);

        printf("리더보드 (시간 적은 순)\n");
        for (int i = 0; i < count; i++)
            printf("%2d. %s: %.2f초\n", i + 1, records[i].name, records[i].time);
    }
    else
    {
        printf("리더보드가 없습니다.\n");
    }
}

int compare_records(const void *a, const void *b)
{
    double t1 = ((Record*)a)->time;
    double t2 = ((Record*)b)->time;
    if (t1 < t2) return -1;
    else if (t1 > t2) return 1;
    else return 0;
}

void countdown(){
    system("cls");
    printf("3");
    Sleep(1000);
    system("cls");
    printf("2");
    Sleep(1000);
    system("cls");
    printf("1");
    Sleep(1000);
    system("cls");
}

// ================== 기존 주판 관련 함수 ===================
void div_number(int mc[], long number)
{
    int i;
    for(i=0;i<=8;i++)
    {
        mc[i]= (int) (number/pow(10, 8-i));
        number= number-(long) pow(10, 8-i)*mc[i];
    }
}

void display_abacus(int m[])
{
    int mc[9];
    for (int i = 0; i < 9; i++) mc[i] = m[i]; // 복사본 사용

    int i, j;

    gotoxy(3, 6);
    for (i = 0; i <= 8; i++) {
        if (m[i] >= 5) printf("｜");
        else printf("◆");
    }

    gotoxy(3, 7);
    for (i = 0; i <= 8; i++) {
        if (m[i] >= 5) printf("◆");
        else printf("｜");
    }

    for (i = 0; i <= 8; i++)
        m[i] %= 5;

    gotoxy(3, 8);
    for (i = 1; i <= 18; i++) printf("─");

    for (i = 1; i <= 5; i++) {
        gotoxy(3, 8 + i);
        for (j = 0; j <= 8; j++) {
            if (m[j] >= i) printf("◆");
            else {
                printf("｜");
                m[j]=5;
            }
        }
    }
}

void draw_rectangle(int c, int r)
{
    int i, j;
    printf("┌");
    for (i = 0; i < c; i++)
        printf("─");
    printf("┐\n");

    for (i = 0; i < r; i++) {
        printf("│");
        for (j = 0; j < c; j++)
            printf(" ");
        printf("│\n");
    }

    printf("└");
    for (i = 0; i < c; i++)
        printf("─");
    printf("┘\n");
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
