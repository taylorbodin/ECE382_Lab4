#include <msp430g2553.h>
#include "pong.h"

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col, unsigned char block_color);

#define		TRUE			1
#define		FALSE			0
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)


void main() {

	int	column, row; // button_press, color;
//	color = FALSE; // The block is filled in
//	button_press = FALSE;
	ball_t myBall;
	myBall = createBall(20,5,1,-1,1);
	column = getX(myBall);
	row = getY(myBall);

	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */

	init();
	initNokia();
	clearDisplay();
	drawBlock(row,column,0);
	while(1) {
		myBall = moveBall(myBall);
		column = getX(myBall);
		row = getY(myBall);
		drawBlock(row,column,0);
		Sleep(100);
		clearDisplay();
		Sleep(20);

//			if (UP_BUTTON == 0) {
//				while(UP_BUTTON == 0);
//				if (y>=1) y=y-1;
//				button_press = TRUE;
//			} else if (DOWN_BUTTON == 0) {
//				while(DOWN_BUTTON == 0);
//				if (y<=6) y=y+1;
//				button_press = TRUE;
//			} else if (LEFT_BUTTON == 0) {
//				while(LEFT_BUTTON == 0);
//				if (x>=1) x=x-1;
//				button_press = TRUE;
//			} else if (RIGHT_BUTTON == 0) {
//				while(RIGHT_BUTTON == 0);
//				if (x<=10) x=x+1;
//				button_press = TRUE;
//			} else if (AUX_BUTTON == 0) {
//				while(AUX_BUTTON == 0);
//				color ^= 1; // toggles the block color flag
//			}
//
//			if (button_press) {
//				button_press = FALSE;
//				drawBlock(y,x,color);
//			}


		}
}
