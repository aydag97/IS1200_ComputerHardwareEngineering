/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   ******************Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);


/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];

/* Declare text buffer for display output */
extern char textbuffer[4][16];

/*************project specific functions*************/

extern uint8_t display[512]; //full display,512 elements, 4096 bits (pixels)
uint8_t pillar[8][2];

void clear_display(void);
void setPixel(int x,int y);
int drawKirby(int x, int y);
void drawPillar(int x, uint8_t obstacle[]);
void drawBorder(void);
int randomNumber();
void movepillar();
int crashPillars(int x, int y);
int crashBorder(int x, int y);
void reset();
void gameover();
void score();
void menu();

int x;
int y;
static int movepillarcounter;
static int randomnumber;
unsigned int clicks;
int scorecounter;