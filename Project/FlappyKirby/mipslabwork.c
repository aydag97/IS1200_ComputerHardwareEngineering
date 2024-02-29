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

int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int *trisE =  (volatile int*) 0xbf886100;
  *trisE = *trisE & ~0xFF;
  
  TRISD = TRISD | 0xFE0; 

  T2CON = 0x70; //prescaling by 256 (111 binary), control register for Timer 2
  TMR2 = 0; //timer value, current time count
  PR2 = ((80000000 / 256) / 10); //31250, period to have en tiondels timeout
  T2CONSET = 0x8000;    //starta timer

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int *portE =  (volatile int*) 0xbf886110;

  while(IFS(0) & 0x100){  //ANDar 8:e biten för IFS (den enda biten vi vill ändra), om den är 1 (är framme i perioden)
      IFS(0) = 0;      //nollställer flaggan
      timeoutcount++;   //increment gloabal countern

      if(timeoutcount == 10){
      timeoutcount = 0;    //nollställer countern för att räkna till 10 igen
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      (*portE)++;
      display_image(96, icon);
    }
  }
  //delay(1000);
  
  //button 0100, nollställ, OR o skifta
  if(getbtns() == 0x4){
    mytime &= 0x0fff;
    mytime = mytime | (getsw()<<12);
  }
  else if(getbtns() == 0x2){
    mytime &= 0xf0ff;
    mytime = mytime | (getsw()<<8);
  }
  else if(getbtns() == 0x1){
    mytime &= 0xff0f;
    mytime = mytime | (getsw()<<4);
  }
  else if(getbtns() == 0x7){
    mytime &= 0x000f;
    mytime = mytime | (getsw() <<12) | (getsw() << 8) | (getsw() << 4);
  }
  else if(getbtns() == 0x3){ //if btn 2 and 3 are pressed the same time
    mytime &= 0xf00f;
    mytime = mytime | (getsw() <<12) | (getsw() << 8) | (getsw() << 4);
  }
  else if(getbtns() == 0x5){
    mytime &= 0x0f0f;
    mytime = mytime | (getsw() <<12) | (getsw() << 8) | (getsw() << 4);
  }
  else if(getbtns() == 0x6){
    mytime &= 0x00ff;
    mytime = mytime | (getsw() <<12) | (getsw() << 8) | (getsw() << 4);
  }

}

/*******************************Project Functions****************************************************/

int x = 15;
int y = 5;
unsigned int clicks;
int scorecounter;

void gamework(){
	//Start the game
  menu();

  //Play the game
	int crashchecks = 1;
	while(!(crashBorder(x, y) == 1)){

  drawKirby(x, y);
	drawBorder();
	movepillar();

  if(crashPillars(x, y) == 1){
    break;
  }
  else if(crashPillars(x, y) == 0){
      crashchecks++;
      if((crashchecks%123) == 0){       // interval to count the score per pillar
        PORTE++;
        scorecounter++;
      }
  }

	y++;

	display_image(0, display);
	clear_display();

	if(getbtns() == 0x4){
    y-=2;
		clicks = clicks ^ (y >> 2) ^ (y ^ (x >> 5)) + 47; // to randomize even more
	}

	quicksleep(100000);
	}

  //Reset the game
	gameover();
	score();
	reset();

}
