#include "../header/unixInput.h"
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#define DEV_PATH "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

static int eventsFd = -1;


void _stopListening(inputArg handleArg){
    unixInputHandler* ul  = (unixInputHandler*)handleArg.arg;
    stopListing(ul); 
}

unixInputHandler unixuInputHandlerInit(){
    
    if (eventsFd == -1){
        eventsFd = open(DEV_PATH,O_RDONLY); 
    }
    unixInputHandler ul;
    ul.eventsSize = -1;

    if(eventsFd == -1){
        return ul;
    }
    
    ul.events = NULL;
    ul.eventsSize = 0;
    ul.listen = false;
    inputHandle ih = newHandle(KEY_PRESSD,KEY_ESC,_stopListening,&ul);
    addHandle(&ul,ih);
    return ul;
}

int addHandle(unixInputHandler* ul , inputHandle ih){
    
    if (ul->eventsSize == 0){
       ul->events = (inputHandle*)malloc(sizeof(inputHandle));
    }else{
       ul->events = (inputHandle*)realloc(ul->events,((ul->eventsSize+1)*sizeof(inputHandle)));
    }
    if(ul->events == NULL){
           return -1;
    }
    
    if(ih.handleArg.arg == NULL){
        ih.handleArg.arg = ul;
    }

    ul->events[ul->eventsSize] = ih;
    ul->eventsSize++;

    return 0;

}

inputHandle newHandle(eventType type , int keyId , void (*handle)(inputArg) , void* arg){
    
    inputHandle event;

    event.type = type;
    event.keyId = keyId;
    event.handle = handle;
    event.handleArg.key_id = keyId;
    event.handleArg.arg = arg;


    return event;
}

int startListening(unixInputHandler* ul){

    int fd = eventsFd;

    struct input_event ev;
    ssize_t n;

    ul->listen = true;

    while (1) {
        if(!(ul->listen)){
            break;
        }

        int eventsCount = ul->eventsSize;

        n = read(fd, &ev, sizeof ev);
        
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
            
            for(int i = 0 ; i < eventsCount ; i++){
                inputHandle currHandle = ul->events[i];
                
                if(currHandle.type == ev.value && currHandle.keyId == ev.code){
                    currHandle.handle(currHandle.handleArg);
                }
            }
        }
    }
    return 0;
}

int removeHandleByIndex(unixInputHandler* ul,int index){
     
    for(int i  = index ; i < ul->eventsSize-1 ; i++){
        ul->events[i] = ul->events[i+1]; 
    }
    ul->eventsSize--;
    if(ul->eventsSize == 0){
        free(ul->events);
        ul->events = NULL;
        return 0;
    }
    ul->events = (inputHandle*)realloc(ul->events,ul->eventsSize*sizeof(inputHandle));
    if (ul->events == NULL) {
        perror("error Realloc in remove Handle");
        return -1;
    }
    return 0;
}

int removeHandleByValue(unixInputHandler* ul, inputHandle inhandle){

    if(inhandle.keyId == KEY_ESC && inhandle.type == KEY_PRESSD && inhandle.handle == _stopListening){
        return -1;
    }
    for(int i = 0 ; i < ul->eventsSize ; i++){
        inputHandle currevent = ul->events[i];
        if(currevent.handle == inhandle.handle && currevent.type == inhandle.type && currevent.keyId == inhandle.keyId){
            return(removeHandleByIndex(ul,i));
        }
    }
    return -1;
}

int removeAllHandles(unixInputHandler* ul){

    free(ul->events);
    ul->eventsSize = 0;
    
    inputHandle ih = newHandle(KEY_PRESSD,KEY_ESC,_stopListening,&ul);
    addHandle(ul,ih);
    return 0;
}

void stopListing(unixInputHandler* arg){
    unixInputHandler* ul = (unixInputHandler*) arg;   
    ul->listen =false;
}

void destroyInputHandler(unixInputHandler* ul){
    if(ul->events!= NULL){
        free(ul->events);
    }
}

int addArrowKyesHandleToInputHandler(unixInputHandler *ul, void(*handle)(inputArg),void* arg){

    addHandle(ul,newHandle(KEY_PRESSD, KEY_UP, handle,arg));
    addHandle(ul,newHandle(KEY_PRESSD, KEY_DOWN, handle,arg));
    addHandle(ul,newHandle(KEY_PRESSD, KEY_RIGHT, handle,arg));
    addHandle(ul,newHandle(KEY_PRESSD, KEY_LEFT, handle,arg));

    return 0;

}

int addNumbersHandleToInputHandler(unixInputHandler *ul, void (*handle) (inputArg),void* arg, bool NUMPAD){

    for(int i = 2 ; i <= 11 ; i++){

        if(addHandle(ul,newHandle(KEY_PRESSD, i, handle,arg))<0){
        
            return -1;
        
        }

    }
    
    if(NUMPAD){

        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP0, handle,arg));

        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP1, handle,arg));
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP2, handle,arg));
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP3, handle,arg));
        
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP4, handle,arg));
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP5, handle,arg));
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP6, handle,arg));

        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP7, handle,arg));
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP8, handle,arg));
        addHandle(ul,newHandle(KEY_PRESSD,KEY_KP9, handle,arg));

    }

    return 0;

}