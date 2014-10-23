#include <msp430g2553.h>
#include "pong.h"

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col, unsigned char block_color);
extern void drawBall(unsigned char row, unsigned char col);

#define		TRUE			1
#define		FALSE			0
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)


void main() {

	int	ballColumn, ballRow, paddleColumn, paddleRow;

	ball_t myBall, paddle;
	myBall = createBall(1,5,1,-1,1);
	ballColumn = getX(myBall);
	ballRow = getY(myBall);

	paddle = createBall(1,5,0,0,1);
	paddleColumn = getX(paddle);
	paddleRow = getY(paddle);
	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */

	init();
	initNokia();
	clearDisplay();
	drawBall(ballRow,ballColumn);
	while(1) {

			if (ballColumn == 0){ //Hit the left side
				clearDisplay();
				while(AUX_BUTTON){
					// Keeps the screen cleared until the aux button is pressed
				}

				myBall = createBall(1,5,1,-1,1);
			}

			if (UP_BUTTON == 0) {
				//while(UP_BUTTON == 0);
				paddleRow--;
				paddle.position.y = paddleRow;
			}

			  else if (DOWN_BUTTON == 0) {
				//while(DOWN_BUTTON == 0);
				paddleRow++;
				paddle.position.y = paddleRow;
			}
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

			myBall = moveBall(myBall);
			ballColumn = getX(myBall);
			ballRow = getY(myBall);

			paddleColumn = getX(paddle);
			paddleRow = getY(paddle);

			drawBall(ballRow,ballColumn);
			drawBlock(paddleRow,paddleColumn,0);

			Sleep(100);
			clearDisplay();
			Sleep(20);

			if(hitBall(myBall,paddle)){
				myBall.velocity.x *= -1;
			}

		}
}
