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

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
 volatile int * trisE = (volatile int*) 0xbf886100;     
 *trisE = *trisE & ~0xFF;                               // 0 = output. maskera 8 lsb.

 TRISD = TRISD | 0xFE0;             // input om det är 1(bitarna 11-5). orade för att inte ändra andra bitar
  return; 
}
/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* portE = (volatile int*) 0xbf886110;
  

  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  (*portE)++;
  display_image(96, icon);

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
