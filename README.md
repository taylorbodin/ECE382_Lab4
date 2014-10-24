ECE382_Lab4
===========

Paint and Pong

## Objectives and Purpose

The objective of this lab was to create an etch-a-sketch like paint program and pong like game in C utilizing 
assembly language functions some of which were provided and some of which we were required to write. 

## Implementation Plan

The implementation for this lab was much more simple than in previous labs due to the fact that much of the code
and functionality was provided. For the first part of the lab we were required to implement an etch-a-sketch from
a working implemenation of a moving brick. To allow us to paint, we need to not clear the screen everytime we move 
the block. To implement the eraser we need to modify the assembly code that writes a block. It needs to take another
parameter (which means adding a register) that will code for a clear block or a filled in block. The new assembly 
subroutine will take this extra parameter and modify the value of the pixels written to the screen. To implement the 
pong game, I broadly plan to bring over my working pong.c and pong.h to the project. I'll use the postion of the ball
object to set the cursor and draw the block. To make the ball visible I'll have to delay the loop so that the ball
doesn't move too fast. I will also add another ball with velocity 0,0 that acts like the paddle and use the buttons 
to modify its postion up and down. Finally I'll have to program a hit detection for the left wall that will trigger 
a game over and a hit detection for the paddle that will alter the velocity of the ball. 

## Functions 

### Sleep

```
//--------------------------------------------------------------------------------
// Author:   C2C Bodin
// Function: Sleep
// Purpose:  Waits for a specified number of ms
//--------------------------------------------------------------------------------
void Sleep(int ms){
	int i, nop;
	nop = 0;

	for(i = 0; i < ms*250; i++){ // As a SWAG, I think this takes about four ms to execute
		nop += 1;
	}

	return;
}
```

Sleep wait's for a specified number of miliseconds. This was implemented by running an four loop that does nothing.
I didn't want to calculate the number of cycles it actually took to run this thing but it wasn't mission critical.
I guessed that 250 repetitions of this program would produce a nice result and it did. With more time I could make the
timing more precise. 

### getX and getY

```
//--------------------------------------------------------------------------------
// Author:   C2C Bodin
// Function: getX, getY
// Purpose:  returns the x or y of ball object
//--------------------------------------------------------------------------------

int getX(ball_t ball){
	int x;
	x = ball.position.x;
	return x;
}

int getY(ball_t ball){
	int y;
	y = ball.position.y;
	return y;
}
```
I took an C++ class once at Colorado School of Mines and I remember being told that it was bad to directly modify the 
values of your objects. Instead you should make functions like these that control access to the objects. To make my code
more readable and reliable I added these functions to return the x and y position of a ball object.

### hitBall

```
char hitBall(ball_t hitter, ball_t hit){
	if(((hit.position.x) == (hitter.position.x)) &&
			((hit.position.y) == (hitter.position.y))){
		return 1;
	}

	else{
		return 0;
	}
}
```

hitBall takes two ball objects and checks to see if they're touching. If they are it returns a one for true and a
zero for false. It was implemented with a simple if statement that checks that the x's match and the y's match. 

### drawBlock

```
drawBlock:
	push	R5
	push	R12
	push	R13
	push	R14

	rla.w	R13					; the column address needs multiplied
	rla.w	R13					; by 8in order to convert it into a
	rla.w	R13					; pixel address.
	call	#setAddress			; move cursor to upper left corner of block

	mov		#1, R12
	mov		#0xFF, R13
	mov.w	#0x08, R5			; loop all 8 pixel columns

	tst.b   R14					; if R14 is 0 then black (0xFF) otherwise it's white (0x00)
	jnz		white
	mov		#0xFF, R13
	jmp		loopdB
white:
	mov		#0x00, R13

loopdB:
	call	#writeNokiaByte		; draw the pixels
	dec.w	R5
	jnz		loopdB

	pop		R14
	pop		R13
	pop		R12
	pop		R5

	ret							; return whence you came
```
	
The majority of this code was provided. I added R14 which serves as a toggle for the block color taking values
of either 1 for clear and 0 for black. I implemented this fucntionality with a simple	tst.b  and jnz.
I selectively loaded R13 with either 0xFF (filled) or 0x00 (unfilled). 
	
### drawBall
	
```
	;-------------------------------------------------------------------------------
;	Name:		drawBall
;	Inputs:		R12 row to draw ball
;				R13	column to draw ball
;
;	Outputs:	none
;	Purpose:	draw an 7 x 7 ball of black pixels at screeen cordinates.
;
;
;	Registers:	R5	column counter to draw all 8 pixel columns
;-------------------------------------------------------------------------------
drawBall:
	push	R5
	push	R12
	push	R13

	rla.w	R13
	rla.w	R13
	rla.w	R13
	call	#setAddress			; move cursor to upper left corner of block

	mov		#1, R12
	mov		#0x38, R13
	call	#writeNokiaByte		; write the left side of the ball
	mov		#0x7C, R13
	call	#writeNokiaByte
	mov.w	#0x03, R5			; loop all 3 middle pixel columns

	mov		#0xFE, R13
	jmp		loopdBall

loopdBall:
	call	#writeNokiaByte		; draw the pixels
	dec.w	R5
	jnz		loopdBall

	mov		#0x7C, R13			; write the right side of the ball
	call	#writeNokiaByte
	mov		#0x38, R13
	call	#writeNokiaByte

	pop		R13
	pop		R12
	pop		R5

	ret							; return whence you came
```
	
Again, a lot of the code for my drawBall was borrowed from drawBlock. I dropped the R14 from this function because
I didn't need to paint with it at this point. I painted the best ball I could in MS paint that fit in an 8x8 square. 
I translated each into their corresponding NokiaByte values and implemented it in the subroutine. As it turned out I
needed three 0xFF bars and so I repurposed loopdB to loopdBall which does the same thing, but only three times. I had
to rename it to to loopdBall because of a compiler error. I was thinking in C where items can be local to functions
and not in assembly where that label is global. 
	
### Main
	
#### Initilizing variables
	
```
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
	
```
	
#### Poll the buttons and alter the values of the paddle accordingly
	
```
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
```

Notice that I left a lot of this code commented out so elements of previous functionality are visible.


#### Update the ball and paddle positions

```
			myBall = moveBall(myBall);
			ballColumn = getX(myBall);
			ballRow = getY(myBall);

			paddleColumn = getX(paddle);
			paddleRow = getY(paddle);
```

#### Redraw the display and delay

```
			drawBall(ballRow,ballColumn);
			drawBlock(paddleRow,paddleColumn,0);

			Sleep(100);
			clearDisplay();
			Sleep(20);
```

the `Sleep(20);` reduces the ghosting, after image effect of the ball moving around the display

#### Check for any paddle hits
```
			if(hitBall(myBall,paddle)){
				myBall.velocity.x *= -1;
			}

		}
}
```

If there is a hit, change the ball's x velocity back the other way. 



## Debugging and Testing

The debugging for this project was much easier and more fun than those in the past because we were working
with the Nokia display. When your program wasn't functioning correctly it was easy to see because the display
wouldn't have anything or be displaying the wrong thing. It also gave clues as to where errors were and what they
looked like. Using this build, run, examine, fix process I was able to achieve full functionality. 

## A functionality

Here is a link to my final, working code. [Here](https://www.youtube.com/watch?v=YqVPotpI3HE&list=UUnEfYJYsfE9CVYEwZqF67PQ)

## Conclusion

I feel very much more comfortable with writing subroutines in assembly, importing them into a c file, and utilizing them.
In the case of the nokia display, the assembly side of things was more precise and could do a lot that could not be done
in C alone. This is a very powerful tool and one I'm excited to exploit. I also enjoyed the object oriented like programing
in this lab. I think OO is some of the coolest stuff around and look forward to more in the future. 

## Documentation

I made use of Stack Overflow to help me through various compiler and linker errors that I received when building code. 
