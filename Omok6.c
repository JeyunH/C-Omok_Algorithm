#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

    char plane[15][15]; // 오목판
    int u, v;
    int idx = 0;
    int cpuPut[2] = {0}; // 컴퓨터 착수
    int pat[4][2] = {{1,0},{1,1},{0,1},{-1,1}}; // 검사 패턴 4가지
        
bool OutOfRange(int a,int b){   // 오목판 범위 밖의 입력인지 판단하는 함수
    return a<1||15<a||b<1||15<b;
}

void CPUfirst(int a, int b){    // CPU가 사용자가 놓은 돌 주변에 랜덤하게 돌을 놓음 -> 첫 돌을 놓을 때 랜덤성 부여
    int cnt = 0;
    int range = 3;
    int x=a;
    int y=b;
    bool flag = true;
    while(flag){
        while(cnt<100){
            x += rand() % range - range/2;
            y += rand() % range - range/2;
            if(!OutOfRange(x,y) && plane[y-1][x-1]=='+' && (x!=a || y!=b)){
                cpuPut[0] = x;
                cpuPut[1] = y;
                flag = false;
            }
            cnt++;
            x=a;
            y=b;
        }
        range+=2;
        cnt = 0;
    }
}

void CPUsecond(int len) // 두번째 착수부터 알고리즘에 따라 동작함
{
    char stone = '+';   // 검사중인 돌 색상 저장할 변수
    int sta[2] = {0};   // 검사중인 돌 시작 위치 저장할 변수
    int end[2] = {0};   // 검사중인 패턴의 커서 위치 저장할 변수
    int pre[2] = {0};   // 검사중인 패턴의 시작 위치의 반대 방향 첫번째 자리의 좌표를 저장할 변수
    int emp[2] = {0};   // 검사중인 패턴에서 비어있는 좌표를 저장할 변수
    char preOC;         // 검사중인 돌 시작 위치의 반대 방향 첫번째 자리가 비었는지 유무를 저장할 변수
    int stack = 0;      // 검사중인 패턴에서 검사중인 돌과 같은 색상의 돌 개수를 저장할 변수
    for(int i=1; i<=15;i++){
        for(int j=1; j<=15;j++) // 오목판 모든 자리 전수조사
        {
            stone = '+';    // 돌색 리셋
            sta[0] = 0;     // 시작 위치 리셋
            sta[1] = 0;
            end[0] = 0;     // 커서 위치 리셋
            end[1] = 0;
            pre[0] = 0;     // 시작 반대 위치 리셋
            pre[1] = 0;
            
            if(plane[i-1][j-1]!='+') // 왼상단부터 우측/하향으로 좌표 확인하다가 돌이 놓여있다면 실행!
            {
                sta[0] = j; // 시작돌 x값 저장
                sta[1] = i; // 시작돌 y값 저장
                stone = plane[i-1][j-1]; // 돌색상 저장 -> B(흑) or W(백)

                for (int s = 1; s <= 4; s++)    // for문 4번 돌려 총 4가지 패턴에 대해서 검사 (우향 가로, 우하향 대각, 하향 세로, 좌하향 대각)
                {
                    end[0] = sta[0]; // 커서 x값 리셋
                    end[1] = sta[1]; // 커서 y값 리셋
                    pre[0] = sta[0]; // 시작위치 반대방향 첫번째 자리 x값 리셋
                    pre[1] = sta[1]; // 시작위치 반대방향 첫번째 자리 y값 리셋
                    emp[0] = 0;     // 비어있는 자리 x좌표 값 리셋
                    emp[1] = 0;     // 비어있는 자리 y좌표 값 리셋
                    stack = 0;      // 연속되는 돌의 수 스택 리셋

                    pre[0]-=pat[s-1][0];
                    pre[1]-=pat[s-1][1];    // 각 패턴에 대해서 시작위치 반대방향 첫번째 자리 좌표를 저장 -> 막혔는지 어떤 돌이 있는지 확인이 필요

                    if(plane[pre[1]-1][pre[0]-1]==stone)   // 시작위치 반대방향 첫번째 돌이 같은 색이면 다음 패턴으로 넘김 -> 이전에 검사했기 때문
                    {
                        continue;
                    }
                    if(!OutOfRange(pre[0],pre[1])&&(plane[pre[1]-1][pre[0]-1]=='+'))  // 시작 돌 반대 방향 첫번째 자리가 막혀있는지 열려있는지 확인
                    {                       // 열린 경우
                        preOC = 'o';        // 열린 상태 저장
                        emp[0] = pre[0];    // 빈자리 변수에 좌표 저장
                        emp[1] = pre[1];
                    }
                    else
                    {                   // 닫힌 경우
                        preOC = 'c';    // 닫힌 상태 저장
                    }

                    for(int k=1; k<=len; k++)   // len(초기값 5)의 크기만큼 반복하여 패턴 방향 len(5)번째 자리까지 같은 돌이 몇 개인지 확인 -> stack올리고 커서 이동 반복
                    {
                        if(!OutOfRange(end[0],end[1]))  // 커서가 오목판 범위 안이라면 실행
                        {
                            if(plane[end[1]-1][end[0]-1]==stone)    // 커서위치의 돌이 시작돌과 같다면 실행
                            {
                                stack++;                // 스택 올리고
                                end[0]+=pat[s-1][0];    // 커서 다음으로 이동
                                end[1]+=pat[s-1][1];
                                continue;               // 동패턴의 다음 돌 검사하러 고고!

                            }else if(plane[end[1]-1][end[0]-1]=='+'){ // 커서위치가 빈자리라면 실행
                                emp[0] = end[0];
                                emp[1] = end[1];        // 빈자리 변수에 커서 좌표 저장하고
                                end[0]+=pat[s-1][0];    // 커서 다음으로 이동
                                end[1]+=pat[s-1][1];
                                continue;               // 동패턴의 다음 돌 검사하러 고고!

                            }else{      // 커서위치에 다른 색 돌이 있을 때 실행
                                break;  // 이번 패턴 반복 종료!
                            }
                        }
                    }
                    if(stack==len)  // 1가지 패턴에 대한 검사가 끝났을 때, stack과 len이 같다면 실행 -> 양쪽 끝 자리 중 빈자리에 돌을 놓게하고 함수 리턴!!
                    {
                        if(preOC=='o')  // 시작 반대 첫자리 비었다면 실행
                        {
                            cpuPut[0] = emp[0];
                            cpuPut[1] = emp[1];
                            return;
                        }
                        else if(!OutOfRange(end[0],end[1]) && plane[end[1]-1][end[0]-1]=='+')   // 끝자리 비었다면 실행
                            {
                                cpuPut[0] = end[0];
                                cpuPut[1] = end[1];
                                return;
                            }
                    }
                    else if(len>=4 && stack==len-1) //len이 3보다 크고 stack=len-1 이라면, 빈공간에 돌을 놓도록하고 함수 리턴!!, 아니라면 pass하여 다음 패턴 검사
                    {       
                        if(emp[0] || emp[1]){ // len-1이 5(4)이고 stack이 4(3)인 경우에 앞뒤가 막힌 경우
                            cpuPut[0] = emp[0]; // emp가 여전히 0이라 cpuPut이 {0,0}인 상태로 return되어 다음 돌들을 검사하지 못하고 넘어가는 문제가 있었음(if문으로 해결)
                            cpuPut[1] = emp[1];
                            return;
                        }
                    }
                }
            }
        }
    }
    //return CPUsecond(len-1); //재귀함수로 만들고 싶은데 아직 못했음
}
    


void DisplayBoard(){    // 바둑판 표시 함수
    for(int y=0; y<15; y++){
        printf("\n");

        if(y==0){   // 가로 범주 표시
            printf("  ");
            for(int z=1; z<=15; z++){
                printf("%x ",z);
            }
            printf("\n");
        }

        printf("%x ", y+1); // 세로 범주 표시


        for(int x=0; x<15; x++){
            printf("%c ", plane[y][x]); // 바둑돌 표시             
        }
    }
}

void Victory(int a, int b, char c){      // 승리 여부 판단하는 함수, 승리시 프로그램 종료
    for(int i=1;i<5;i++){
        int stack = 0;
        int x = a;
        int y = b;
        while(1){
            if(stack<5){
                if(!OutOfRange(x,y))
                {
                    if(plane[y-1][x-1]==c)
                    {
                        stack++;
                        x+=pat[i-1][0];
                        y+=pat[i-1][1];                      
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                switch(c)
                {
                    case 'B':
                    DisplayBoard();
                    printf("\nBlack Win!\n");
                    break;
                    case 'W':
                    DisplayBoard();
                    printf("\nWhite Win!\n");
                }
                system("pause");
                exit(0);            
            }
        }
    }
}

void InputPosition(){
    while(1){   // 빈 자리에 안놓으면 while문 반복!

        if(idx%2 == 0){ // 검은 돌 차례 표시
            printf("\nPut the black stone:");
            scanf("%d, %d", &u, &v);    // 사용자 입력 받기
        }else{          // 흰 돌 차례 표시
            printf("\nPut the white stone:");
            for (int i = 5; 0 < i; i--)
            {
                if(idx==1)
                {
                    CPUfirst(u,v);
                    break;
                }
                CPUsecond(i);
                //CPUsecond(5);
                printf("\nlen: %d, x: %d, y: %d",i,cpuPut[0],cpuPut[1]);
                if(cpuPut[0]!=0 || cpuPut[1]!=0){
                    break;
                }
            }
            u = cpuPut[0];
            v = cpuPut[1];
            printf("\n%d,%d\n",u,v);
            cpuPut[0] = 0;
            cpuPut[1] = 0;
        }     
            if(OutOfRange(u,v)){    // 배열의 index 범위 밖의 입력인 경우
                DisplayBoard();
                printf("\nInput is out of range");
                continue;       // 다시 while문 돌려~
            }else if(plane[v-1][u-1]!='+'){     // 놓은 자리에 또 놓으려는 경우
                DisplayBoard();
                printf("\nThere's already a stone");
                continue;       // 다시 while문 돌려~
            }

            plane[v-1][u-1] = (idx%2+1==1)?'B':'W';    // 빈 자리에 정상적으로 놓은 경우

            for(int i=1; i<15; i++){    // 승리 여부 판단
                for(int j=1; j<15; j++){
                    Victory(j,i,(idx%2+1==1)?'B':'W');
                }
            }

            idx++;      // 턴 넘김
            break;      // while문 탈출!
    }
}

int main(){
    srand(time(NULL));  // 난수 시드 설정

    for(int y=0; y<15; y++)
        for(int x=0; x<15; x++)
            plane[y][x] = '+';   // 배열 초기화

    while(1){   // 반복하면서 바둑판 표시하고 입력받고 승리여부 판단을 수행
        DisplayBoard();
        InputPosition();
        
    }
    printf("end of code\n");
    return 0;
}

