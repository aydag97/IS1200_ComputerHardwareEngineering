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


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}


/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trisE = (volatile int*) 0xbf886100;
  *trisE = *trisE & ~0xFF;


  TRISD = TRISD | 0xFE0; 

 
  T2CON =0X70;          // Prescale 256:1. change bits 4,5,6
  PR2 = 31250;          // Period to have 100 ms timeouts
  TMR2 = 0;             // CURRENT TIME COUNT
  T2CONSET = 0x8000;     // start the timer

  return;
}
/* This function is called repetitively from the main program */
void labwork( void )
{
  static volatile int* portE = (volatile int*) 0xbf886110;
 
  while(IFS(0) & 0x100){ // if bit index 8(flag) == 1
    IFS(0) = 0;           // nollställer flaggan
    timeoutcount++;
    if(timeoutcount == 10){
    timeoutcount = 0;     // nollställer counter
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    (*portE)++;
    display_image(96, icon);
  }
  }

  int retsw = getsw();
 
  if(getbtns() == 0x4){     // pressing button 4
    mytime &= 0x0fff;       // nollställa relevanta bitar
    mytime |= (retsw<<12);  // shiftar bitarna till rätt plats och updaterar mytime
  }


  if(getbtns() == 0x2){     // pressing button 3
    mytime &= 0xf0ff;      
    mytime |= (retsw<<8);  
  }
  if(getbtns() == 0x1){     // pressing button 2
    mytime &= 0xff0f;
    mytime |= (retsw<<4);
  }
  if(getbtns() == 0x3){     // pressing button 3 & 2
    mytime &= 0xf00f;
    mytime = mytime | (retsw<<4) | (retsw<<8);
  }
  if(getbtns() == 0x5){     // pressing button 4 & 2
    mytime &= 0x0f0f;
    mytime = mytime | (retsw<<4) | (retsw<<12);
  }
  if(getbtns() == 0x6){     // pressing button 3 & 4
    mytime &= 0x00ff;
    mytime = mytime | (retsw<<12) | (retsw<<8);
  }
  if(getbtns() == 0x7){     // pressing buttons 4 & 3 & 2
    mytime &= 0x000f;
    mytime = mytime | (retsw<<4) | (retsw<<8) | (retsw<<12);
  }
}
