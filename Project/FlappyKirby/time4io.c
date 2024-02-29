#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ){
    
    int val;
    val = PORTD & 0xF00;       

    val = (val >> 8);
    return val;
}

int getbtns(void){
    
    int val;
    val = PORTD & 0xE0;
    
    val = (val >> 5);
    return val;

}