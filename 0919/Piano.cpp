#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

int calc_frequency(int octave, int key);
void play_piano(void);
void play_sheet(string filename);
int note_index[] = {0, 2, 4, 5, 7, 9, 11, 12};
int freq[8];

int main(void){
    int command, sheet_choice;

    for(int i = 0; i < 8; i++){
        freq[i] = calc_frequency(4, note_index[i]); // 4옥타브의 도~도까지의 주파수를 배열에 저장
    }
    
    do{
        system("cls");
        printf("=== 피아노 프로그램 ===\n");
        printf("1번:피아노실행 2:악보출력\n");
        printf("종료(Esc)\n");
        command = getch();
        switch (command)
        {
        case '1':
            system("cls");
            printf("1부터 8까지 숫자 키를 누르면\n");
            printf("각 음의 소리가 출력됩니다.\n\n");
            printf("1:도 2:레 3:미 4:파 5:솔 6:라 7:시 8:도\n");
            printf("뒤로가기(Esc)\n");
            play_piano();
            break;
        case '2':
            system("cls");
            printf("악보를 선택하세요\n");
            printf("1: 아리랑\n");
            printf("2: 학교종이 땡땡땡\n");
            sheet_choice = getch();
            switch(sheet_choice) {
                case '1':
                    play_sheet("arirang.txt");
                    break;
                case '2':
                    play_sheet("schoolbell.txt");
                    break;
                default:
                    printf("잘못된 악보 번호입니다.\n");
                    break;
            }
            break;
        case 27:
            printf("프로그램을 종료합니다...\n");
            break;
        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    } while (command!=27); // Ese키 입력까지 반복

    return 0;
}

int calc_frequency(int octave, int key){
    double do_scale = 32.7032;
    double ratio = pow(2., 1/12.), temp;
    temp = do_scale*pow(2, octave-1);
    for(int i = 0; i < key; i++){
        temp = (int) (temp+0.5);
        temp *= ratio;
    }
    return (int) temp;
}

void play_piano(void){
    int code;
    do
    {
        code = getch();
        if('1'<=code && code<='8'){
            code -= 49;
            Beep(freq[code], 300);
        }
    } while (code!=27); // Ese키 입력까지 반복
}

void play_sheet(string filename){
    FILE *fp = fopen(filename.c_str(), "r");
    if(fp == NULL){
        printf("파일 열기 실패\n");
        return;
    }

    int note, length;
    int bpm = 120;
    while(fscanf(fp, "%d %d", &note, &length) == 2){
        double beat_ms = 60000.0 / bpm; // 4분 음표 = 60000/BPM
        int duration = (int) (beat_ms * (4.0 / length));

        if(note == 0){
            Sleep(duration); // 쉼표
        }
        else if(1<=note && note<=8){
            Beep(freq[note-1], duration);
        }
        Sleep(50);
    }
    
    fclose(fp);
}