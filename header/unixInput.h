
#ifndef UNIXINPUT_H_
#define UNIXINPUT_H_

#include <stdbool.h>
#include <linux/input.h>
#include <unistd.h>

typedef enum eventType{
    KEY_RELEASED, 
    KEY_PRESSD,   
    KEY_REPEATED 

}eventType;

typedef struct inputArg{
    
    int key_id;

    void* arg;

}inputArg;

typedef struct _inputH{
  
    eventType type; 
  
    int keyId; 
  
    void (*handle)(inputArg);

    inputArg handleArg;
    
}inputHandle;

typedef struct _unixInputHandler{

    inputHandle* events; 

    int eventsSize;

    bool listen;

}unixInputHandler;



unixInputHandler unixuInputHandlerInit();

inputHandle newHandle(eventType type , int keyId , void (*handle)(inputArg) , void* arg);

int addArrowKyesHandleToInputHandler(unixInputHandler *ul, void (*handle)(inputArg),void* arg);

int addNumbersHandleToInputHandler(unixInputHandler *ul, void (*handle)(inputArg) ,void * arg, bool NUMPAD);

int addHandle(unixInputHandler* ul , inputHandle ih);

int removeHandleByValue(unixInputHandler* ul, inputHandle inhandle);

int removeAllHandles(unixInputHandler* ul);

int startListening(unixInputHandler* ul);

void stopListing(unixInputHandler*  ul);

void destroyInputHandler(unixInputHandler* ul);

#endif //UNIXINPUT_H_



