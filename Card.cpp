#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct trump{ //카드 구조체 
   char order;
   char shape[4];
   char number;
};

char shape[4][4] = {"♠", "♦", "♥", "♣"}; //2차원 배열, 4개의 문자가 3Byte(확장코드)+1Byte(Null) 
void make_card(trump m_card[]);
void display_card(trump m_card[]);
void shuffle_card(trump m_card[]);


int main(void){
   trump card[52];
   make_card(card);
   shuffle_card(card);
   display_card(card);
   return 0;
}


void make_card(trump m_card[]){ //카드 생성 
   for(int i=0;i<4;i++){
      for(int j=i*13;j<i*13+13;j++){
         m_card[j].order = i;
         strcpy(m_card[j].shape, shape[i]);
         m_card[j].number = j%13+1;
         switch(m_card[j].number){
            case 1:
               m_card[j].number = 'A';
               break;
            case 11:
               m_card[j].number = 'J';
               break;
            case 12:
               m_card[j].number = 'Q';
               break;
            case 13:
               m_card[j].number = 'K';
               break;
         }
         //printf("카드 생성 완료 %d\n", j);
      }
   }
}

void display_card(trump m_card[]){ //카드 출력 
   for(int i=0;i<52;i++){
      printf("%s", m_card[i].shape);
      if(m_card[i].number=='A'||m_card[i].number=='J'||m_card[i].number=='Q'||m_card[i].number=='K') { printf("%-2c ", m_card[i].number); }
      else { printf("%-2d ", m_card[i].number); }
      if (i%13==12){
         printf("\n");
      }
   }
}

void shuffle_card(trump m_card[]){
   int i, rnd;
   trump tmp;
   srand(time(NULL)); // 난수의 초기화
   for(int i = 0; i<52; i++){
      rnd = rand()%52;
      tmp = m_card[rnd];
      m_card[rnd] = m_card[i];
      m_card[i] = tmp;
   }
}