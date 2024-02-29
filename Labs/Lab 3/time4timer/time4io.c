#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
    int val = PORTD & 0xF00;       // vi andar med 0x780 för att ta ut bitarna 8 till 11 och sparar i val.
    val = val >> 8;             // vi shiftar för att bitarna ska vara i lsb.

    return val;
}

int getbtns (void){
    
    int val = PORTD & 0xE0;       // vi andar med 0x70 för att ta ut bitarna 5-7 och sparar i val.
    val = val >> 5;             // vi shiftar för att bitarna ska vara i lsb.

    return val;

}