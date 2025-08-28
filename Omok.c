#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
    int plane[9][9];
    int u, v;
    int idx = 0; 
        
bool OutOfRange(int a,int b){   // plane 배열의 index 범위 밖의 입력인지 판단하는 함수
    return a<1||9<a||b<1||9<b;
}

void DisplayBoard(){    // 바둑판 표시 함수
    for(int y=0; y<9; y++){
        printf("\n");

        if(y==0){           // 가로 좌표 표시
            printf("  ");
            for(int z=1; z<=9; z++){
                printf("%d ",z);
            }
            printf("\n");
        }

        printf("%d ", y+1);     // 세로 좌표 표시

        for(int x=0; x<9; x++){     // 바둑돌 표시
            printf("%d ", plane[y][x]);                
        }
    }
}

void Victory(int a, int b, int c){      // 승리 여부 판단하는 함수, 승리시 프로그램 종료
    for(int i=1;i<5;i++){
        int stack = 0;
        int x = a;
        int y = b;
        while(1){
            if(stack<5){
                if(!OutOfRange(x,y)){
                    if(plane[y-1][x-1]==c){
                        switch(i){
                            case 1:
                                stack++;
                                x++;
                                break;
                            case 2:
                                stack++;
                                x++;
                                y++;
                                break;
                            case 3:
                                stack++;
                                y++;  
                                break;
                            case 4:
                                stack++;
                                x--;
                                y++;
                        }                        
                    }else{
                        break;
                    }
                }else{
                    break;
                }
            }else{
                switch(c){
                    case 1:
                    DisplayBoard();
                    printf("\n흑돌이 승리했습니다!");
                    break;
                    case 2:
                    DisplayBoard();
                    printf("\n백돌이 승리했습니다!");
                }                
                exit(0);            
            }
        }
    }
}

void InputPosition(){
    while(1){   // 빈 자리에 안놓으면 while문 반복!

        if(idx%2 == 0){ // 검은 돌 차례 표시
            printf("\nDrop the black stone:");
        }else{          // 흰 돌 차례 표시
            printf("\nDrop the white stone:");
        }
            scanf("%d, %d", &u, &v);    // 사용자 입력 받기
            if(OutOfRange(u,v)){    // 배열의 index 범위 밖의 입력인 경우
                DisplayBoard();
                printf("\nInput is out of range");
                continue;       // 다시 while문 돌려~
            }else if(plane[v-1][u-1]!=0){     // 놓은 자리에 또 놓으려는 경우
                DisplayBoard();
                printf("\nThere's already a stone");
                continue;       // 다시 while문 돌려~
            }
            plane[v-1][u-1] = idx%2+1;    // 빈 자리에 정상적으로 놓은 경우

            for(int i=1; i<10; i++){    // 승리 여부 판단
                for(int j=1; j<10; j++){
                    Victory(j,i,idx%2+1);
                }
            }

            idx++;      // 턴 넘김
            break;      // while문 탈출!
    }
}

int main(){
    for(int y=0; y<9; y++)
        for(int x=0; x<9; x++)
            plane[y][x] = 0;   // 배열 초기화

    while(1){   // 반복하면서 바둑판 표시하고 입력받고 승리여부 판단을 수행
        DisplayBoard();
        InputPosition();
        
    }
    printf("end of code\n");
    return 0;
}

