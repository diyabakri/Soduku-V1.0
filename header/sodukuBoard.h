#ifndef SODUKUBOARD_H_
#define SODUKUBOARD_H_


typedef struct sodukuBoard{
    unsigned short board[9][9];
    unsigned short numCount;
}sodukuBoard;

void showSeleution(sodukuBoard* B);

static sodukuBoard seleution;

sodukuBoard sodukuBoardInit();

void printSodukuBoard(sodukuBoard Board,int slected_i , int selected_j);

int setBox(sodukuBoard* B, int row , int col , int value );

sodukuBoard generateGame(int size);

short getDomain(sodukuBoard* B , int selected_i , int selected_j);

int checkDomain(sodukuBoard* B , int row , int col , int value);

int solve(sodukuBoard B , int i , int j);

int checkBoardValid(sodukuBoard B);

int getCount();

void resetCount();

void saveSeleution(sodukuBoard B);

void inputListner( void* arg);

#endif//SODUKUBOARD_H_