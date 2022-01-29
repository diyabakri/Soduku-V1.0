#ifndef SODUKUBOARD_H_
#define SODUKUBOARD_H_


typedef struct sodukuBoard{
    unsigned short board[9][9];
    unsigned short numCount;
}sodukuBoard;
/**
 * @brief showSeletuion() shows the selelution of the current board  
 * 
 * @param B 
 */
void showSeleution(sodukuBoard* B);
/**
 * @brief static var for holding the seleution
 * 
 */
static sodukuBoard seleution;
/**
 * @brief retuns an initialized sodukuBoard 
 * 
 * @return sodukuBoard var with all the spaces set to 0
 */
sodukuBoard sodukuBoardInit();
/**
 * @brief prints the board in on the termnal with the use of the "clear" command to keep the boeard centered in the screen
 * 
 * @param Board 
 * @param slected_i the row index of the current selected box
 * @param selected_j the col index of the current selected box
 */
void printSodukuBoard(sodukuBoard Board,int slected_i , int selected_j);
/**
 * @brief Set the Box with the given value 
 * 
 * @param B 
 * @param row 
 * @param col 
 * @param value 
 * @return int 0 if the value was set -1 otherwise
 */
int setBox(sodukuBoard* B, int row , int col , int value );
/**
 * @brief creates a new valid soduku game board by usning random values
 * 
 * @param size number of preset boxes to generate Note setting the size over 40 may couse long genetarting times 
 * @return sodukuBoard the new generated board
 */
sodukuBoard generateGame(int size);
/**
 * @brief Get the Domain of a selected box
 * 
 * @param B 
 * @param selected_i 
 * @param selected_j 
 * @return short the values that are allowed in the box in binary string
 */
short getDomain(sodukuBoard* B , int selected_i , int selected_j);
/**
 * @brief chack if a value is allowed in a given box
 * 
 * @param B 
 * @param row 
 * @param col 
 * @param value 
 * @return int 0 if allowed -1 if not
 */
int checkDomain(sodukuBoard* B , int row , int col , int value);
/**
 * @brief solves a given board with recursion with backtracking 
 * 
 * @param B 
 * @param i 
 * @param j 
 * @return int 1 if the board has one seletion 2 if more 0 if its unsolveable
 */
int solve(sodukuBoard B , int i , int j);
/**
 * @brief checks if the board is valid and can be solved
 * 
 * @param B 
 * @return int 0 valid -1 not valid
 */
int checkBoardValid(sodukuBoard B);
/**
 * @brief Get the seletion Count 
 * 
 * @return int seletion counter value
 */
int getCount();
/**
 * @brief sets the seleutions counter to 0
 * 
 */
void resetCount();
/**
 * @brief saves the solution of a given board to be shown later
 * 
 * @param B 
 */
void saveSeleution(sodukuBoard B);
/**
 * @brief main click handler
 * 
 * @param arg 
 */
void inputListner( void* arg);

#endif//SODUKUBOARD_H_