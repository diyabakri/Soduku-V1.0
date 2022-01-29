#include <stdio.h>
#include "./header/sodukuBoard.h"
#include "./header/unixInput.h"
#include <time.h>
#include <stdlib.h>

sodukuBoard b;

int inBoardI=0,inBoardJ=0,inMenuI=0,inOptionI=0,inSavesI=0;
bool playing = true;


void inGameInputHandler(inputArg handleArg){

    int key = handleArg.key_id;
    unixInputHandler* currl = (unixInputHandler*) (handleArg.arg); 
    if(key<=KEY_9 && key>=KEY_1){
    
        setBox(&b,inBoardI,inBoardJ,key-1);    

    }else if(key<=KEY_KP3 && key>=KEY_KP7){

        switch (key)
        {
        case KEY_KP9:
            setBox(&b,inBoardI,inBoardJ,9);
            break;
        case KEY_KP8:
            setBox(&b,inBoardI,inBoardJ,8);
            break;
        case KEY_KP7:
            setBox(&b,inBoardI,inBoardJ,7);
            break;
        case KEY_KP6:
            setBox(&b,inBoardI,inBoardJ,6);
            break;
        case KEY_KP5:
            setBox(&b,inBoardI,inBoardJ,5);
            break;
        case KEY_KP4:
            setBox(&b,inBoardI,inBoardJ,4);
            break;
        case KEY_KP3:
            setBox(&b,inBoardI,inBoardJ,3);
            break;
        case KEY_KP2:
            setBox(&b,inBoardI,inBoardJ,2);
            break;
        case KEY_KP1:
            setBox(&b,inBoardI,inBoardJ,1);
            break;
        }
    }else{

        switch (key)
        {
        case KEY_UP:
            inBoardI--;
            break;
        case KEY_DOWN:
            inBoardI++;
            break;
        case KEY_LEFT:
            inBoardJ--;
            break;
        case KEY_RIGHT:
            inBoardJ++;
            break;
        case KEY_BACKSPACE:
            setBox(&b,inBoardI,inBoardJ,0);
            break;
        case KEY_S:
            showSeleution(&b);
            stopListing(currl);
            return;
            break;

        }
        if(inBoardI < 0){
            inBoardI+=9;
        }
        if(inBoardJ < 0){
            inBoardJ+=9;
        }
        inBoardJ = inBoardJ%9;
        inBoardI = inBoardI%9;
    }

    printSodukuBoard(b, inBoardI, inBoardJ);
    if(b.numCount == 81){
        stopListing(currl);
    }
}

void postGameContinueHandle(inputArg arg){
        unixInputHandler* ul = (unixInputHandler*) arg.arg;
        removeAllHandles(ul);
        stopListing(ul);
        playing = true;
        return;
}

void postGameStop(inputArg arg){

    unixInputHandler* ul = (unixInputHandler*) arg.arg;
    removeAllHandles(ul);
    stopListing(ul);

    return;
}

int main(){

    unixInputHandler sodukuInputHandler;
    sodukuInputHandler = unixuInputHandlerInit();

    inputHandle backspace_handle =  newHandle(KEY_PRESSD,KEY_BACKSPACE,inGameInputHandler,NULL);
    inputHandle solve_handle = newHandle(KEY_PRESSD,KEY_S,inGameInputHandler,NULL);
    inputHandle yes_handle = newHandle(KEY_PRESSD, KEY_Y, postGameContinueHandle,NULL);
    inputHandle no_handle = newHandle(KEY_PRESSD, KEY_N, postGameStop,NULL);


    while (playing){

        srand(clock());

        while (getCount() < 1){ 
            resetCount();
            b = generateGame(30);
            printf("\t\t\t  Generating valid Board");
            printSodukuBoard(b, -1, -1);
            usleep(25000);
            solve(b, 0, 0);
        }

        resetCount();
        inBoardI = 0;
        inBoardJ = 0;
        printSodukuBoard(b, inBoardI, inBoardJ);
        
        printf("\t\t\tPress arrow keys to move position\n");
        printf("\t\t Press number keys to change the value of a box\n");
        printf("\t\tPress the backspace key to remove number from box\n");
        printf("\t\t Press the s key to automaticly solve the puzzle\n");

        addHandle(&sodukuInputHandler,backspace_handle);
        addHandle(&sodukuInputHandler,solve_handle);
        addArrowKyesHandleToInputHandler(&sodukuInputHandler,inGameInputHandler,NULL);
        addNumbersHandleToInputHandler(&sodukuInputHandler,inGameInputHandler,NULL,true);
        
        playing = false;
    
        startListening(&sodukuInputHandler);

        removeAllHandles(&sodukuInputHandler);        
        
        addHandle(&sodukuInputHandler,yes_handle);
        addHandle(&sodukuInputHandler,no_handle);

        printf("\t\t\t Play new game ? (y/n)\n");

        startListening(&sodukuInputHandler);

        
    }
    destroyInputHandler(&sodukuInputHandler);
    return 0;

}
