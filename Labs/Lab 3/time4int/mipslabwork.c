/* mipslabwork.c


   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall


   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):


   This file modified 2017-04-31 by Ture Teknolog


   For copyright and licensing, see file COPYING */


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";
static int timeoutcount = 0;
int prime = 1234567;


/* Interrupt Service Routine */
void user_isr( void ) {
  timeoutcount++;
  IFSCLR(0) = 0x100;            // reset bit 8 in IFS0 (T2IF i IFS0)
 
  if(timeoutcount == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeoutcount = 0;
  }
 
  return;
}


/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trisE = (volatile int*) 0xbf886100;
  *trisE = *trisE & ~0xFF;


  TRISD = TRISD | 0xFE0;


 
  T2CON =0X70;            // Prescale 256:1. change bits 4,5,6
  PR2 = 31250;            // Period to have 100 ms timeouts
  TMR2 = 0;               // CURRENT TIME COUNT
  T2CONSET = 0x8000;      // start the timer


  IEC(0) = 0x100;         // enable timer 2 interrupts (bit 8-T2IE)
 // IPC(2) = 7;             // highest priority (bits 4-2). sättor ettor i alla platser i bitarna 4-2


  /*volatile int *IEC = (volatile int*) 0XBF881060;
  volatile int *IPC2 = (volatile int*) 0xbf8810b0;
 
  *IEC = 0X100;
  *IPC2 = *IPC2 | 0x1c;*/


  enable_interrupt();       // enable interrupt globally


  return;
}
/* This function is called repetitively from the main program */
void labwork( void ) {
prime = nextprime( prime );
display_string( 0, itoaconv( prime ) );
display_update();
}

