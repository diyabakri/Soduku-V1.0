#include "../header/sodukuBoard.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

short preset_index[9][9];
static int count = 0;


sodukuBoard generateGame(int size){

    sodukuBoard B = sodukuBoardInit();
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            preset_index[i][j] = 0;
        }
    }
    int counter = 0;
    int rand1,rand2,rand3;
    
    
        while(1){
    
            rand1 = rand()%9;
            rand2 = rand()%9;
            rand3 = (rand()%9)+1;
    
            if(setBox(&B,rand1,rand2,rand3)==0){
                counter++;
                preset_index[rand1][rand2] = 1;
            }
            if(counter == size){
                
                break;
            }
    
        }
        
    return B;
}

int setBox(sodukuBoard* B, int row , int col, int value){
    
    if(preset_index[row][col]){
        return -1;
    }
    
    if(value < 0 && value > 9){
        return -1;
    }

    if (value != 0){    
        if(checkDomain(B,row,col,value)==0){
            B->board[row][col] = value;
            B->numCount++;
        }else{
            return -1;
        }    
    }else{
        B->board[row][col] = value;
        B->numCount--;
    }
    return 0;
}

int checkBoardValid(sodukuBoard B){
    
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            int c = 0;
            if(B.board[i][j]>0){
                continue;
            }
            if(getDomain == 0){
                return -1;
            }
        }
    }
    return 0;
}

int checkDomain(sodukuBoard* B , int row , int col , int value){

    int box_i = row/3;
    box_i += ((box_i*2)+1);
    int box_j = col/3;
    box_j += ((box_j*2)+1);

    if (B->board[box_i][box_j] == value){
        return -1;
    }
    if (B->board[box_i-1][box_j-1]== value){
        return -1;
    }
    if (B->board[box_i+1][box_j+1]== value){
        return -1;
    }
    if (B->board[box_i-1][box_j+1]== value){
        return -1;
    }
    if (B->board[box_i+1][box_j-1]== value){
        return -1;
    }
    if (B->board[box_i][box_j-1]== value){
        return -1;
    }
    if (B->board[box_i][box_j+1]== value){
        return -1;
    }
    if (B->board[box_i-1][box_j]== value){
        return -1;
    }
    if (B->board[box_i+1][box_j]== value){
        return -1;
    }

    for(int i = 0 ; i < 9 ; i++){
        if(B->board[i][col]== value){
            return -1;
        }
        if(B->board[row][i]== value){
            return -1;
        }
    }
    return 0;

}

sodukuBoard sodukuBoardInit(){
    sodukuBoard s;
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            s.board[i][j]=0;
        }
    }
    s.numCount = 0;
    return s;
}

void printSodukuBoard(sodukuBoard Board, int selected_i , int selected_j){
    system("clear");

    int box_i = selected_i/3;
    box_i += ((box_i*2)+1);
    int box_j = selected_j/3;
    box_j += ((box_j*2)+1);
    
    for(int i = 0 ; i <4 ; i++){
        printf("\n");
    }
    short domain = getDomain(&Board,selected_i,selected_j);
    if(!(preset_index[selected_i][selected_j])){
        printf("\t\t\t possible values: ");
        for(int i = 0 ; i < 9 ; i++){
            if(domain&(0x1<<i)){
                printf("%d ",(i+1));
            }
        }
    }
    printf("\n");
    for(int i =0 ; i <9 ; i++){
        printf("\t\t\t");

        if ((i+3) % 3 == 0){
            
            for(int j = 0 ;j < 9 ; j++){
                printf("---");
            }
            printf("--");
            printf("\n");
            printf("\t\t\t");
        }

        for(int j = 0 ;j < 9 ; j++){
            if(Board.board[i][j]!=0){
            printf("|%hu|",Board.board[i][j]);
            }else{
                if(selected_i >= 0 && (i != selected_i || j != selected_j)){
                    if((i == selected_i || j == selected_j) || (( i<= box_i+1 && i>= box_i-1 )&& (j<= box_j+1 && j>= box_j-1))){
                    
                        printf("|#|");
                    }else{
                        printf("| |");
                    }
                }else{
                    printf("|X|");
                }
            }
            if ((j+1) % 3 == 0){
                printf(" ");
            }
        }
        printf("\n");
    }
    
    printf("\t\t\t");
    for(int i = 0 ;i < 9 ; i++){
        printf("---");
    }
    printf("--");
    printf("\n");

}

int solve(sodukuBoard B , int i , int j){
    if(i == 8 && j == 9){
        count++;
        saveSeleution(B);
        return 1;
    }
    if( j == 9){
        j=0;
        i++;
    }
    if(B.board[i][j]> 0){
        solve(B,i,j+1);
    }else{
    
        int n = 1;  

        while(n<10){
            
            if(setBox(&B,i,j,n)!=-1){
                
                if(count>1){
                    return 0;
                }
                solve(B,i,j+1);
                setBox(&B,i,j,0);
            }
            n++;
        }
        return 0;
    }
    return 0;
}

void saveSeleution(sodukuBoard B){

    seleution = sodukuBoardInit();

    for(int i = 0 ; i < 9 ; i++ ){

        for(int j = 0 ; j < 9 ; j++){
        
            seleution.board[i][j] = B.board[i][j]; 
        
        }
    
    }
    return;
}

void showSeleution(sodukuBoard* B){

    for(int i = 0 ; i < 9 ; i++ ){

        for(int j = 0 ; j < 9 ; j++){
        
            B->board[i][j] = seleution.board[i][j];
            usleep(25000);
            printSodukuBoard(*B,-1,-1);
        }
    
    }

}

int getCount(){
    return count;
}

void resetCount(){
    count = 0;
}

short getDomain(sodukuBoard* B , int selected_i , int selected_j){
    
    short Domain = 0x1ff;

    int box_i = selected_i/3;
    box_i += ((box_i*2)+1);
    int box_j = selected_j/3;
    box_j += ((box_j*2)+1);

    if (B->board[box_i][box_j] != 0){
        Domain &= ~(0x1<<B->board[box_i][box_j]-1);
    }
    if (B->board[box_i-1][box_j-1]!= 0){
        Domain &= ~(0x1<<B->board[box_i-1][box_j-1]-1);

    }
    if (B->board[box_i+1][box_j+1]!= 0){
        Domain &= ~(0x1<<B->board[box_i+1][box_j+1]-1);

    }
    if (B->board[box_i-1][box_j+1]!= 0){
        Domain &= ~(0x1<<B->board[box_i-1][box_j+1]-1);

    }
    if (B->board[box_i+1][box_j-1]!= 0){
        Domain &= ~(0x1<<B->board[box_i+1][box_j-1]-1);

    }
    if (B->board[box_i][box_j-1]!= 0){
        Domain &= ~(0x1<<B->board[box_i][box_j-1]-1);

    }
    if (B->board[box_i][box_j+1]!= 0){
        Domain &= ~(0x1<<B->board[box_i][box_j+1]-1);

    }
    if (B->board[box_i-1][box_j]!= 0){
        Domain &= ~(0x1<<B->board[box_i-1][box_j]-1);

    }
    if (B->board[box_i+1][box_j]!= 0){
        Domain &= ~(0x1<<B->board[box_i+1][box_j]-1);

    }

    for(int i = 0 ; i < 9 ; i++){
        if(B->board[i][selected_j]!= 0){
            Domain &= ~(0x1<<B->board[i][selected_j]-1);
        }
        if(B->board[selected_i][i]!= 0){
            Domain &= ~(0x1<<B->board[selected_i][i]-1);
        }
    }

    return Domain;
}

