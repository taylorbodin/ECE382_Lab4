#include "pong.h"

//--------------------------------------------------------------------------------
// Author:   C2C Bodin
// Function: createBall
// Purpose:  Initializes the ball object, can also be used to update the same ball
//--------------------------------------------------------------------------------

ball_t createBall(int xPos, int yPos, int xVel, int yVel, unsigned char radius){
	vector2d_t ballPos, ballVel;
	ball_t ball;

	ballPos.x = xPos;
	ballPos.y = yPos;

	ballVel.x = xVel;
	ballVel.y = yVel;

	ball.position = ballPos;
	ball.velocity = ballVel;
	ball.radius   = radius;

	return ball;
}

//--------------------------------------------------------------------------------
// Author:   C2C Bodin
// Function: moveBall
// Purpose:  Updates the ball position using the velocity structure. Checks the ball
//			position for collision with the walls
//--------------------------------------------------------------------------------

ball_t moveBall(ball_t ballToMove){
	ballToMove.position.x += ballToMove.velocity.x;		// The new position is the current position plus the change in position i.e. velocity
	ballToMove.position.y += ballToMove.velocity.y;

	if(hitTop(ballToMove)){
		ballToMove.position.y  = 0;						// If we hit we set the position to the edge so the ball doesn't go inside
		ballToMove.velocity.y *= -1;					// The ball "bounces" by reversing the inverting after a hit
		return ballToMove;
	}

	if(hitBot(ballToMove)){
		ballToMove.position.y  = (SCREEN_HEIGHT - ballToMove.radius);
		ballToMove.velocity.y *= -1;
		return ballToMove;
	}

	if(hitLeft(ballToMove)){
		ballToMove.position.x  = 0;
		ballToMove.velocity.x *= -1;
		return ballToMove;
	}

	if(hitRight(ballToMove)){
		ballToMove.position.x  = (SCREEN_WIDTH - ballToMove.radius);
		ballToMove.velocity.x *= -1;
		return ballToMove;
	}

	else{
		return ballToMove;
	}
}

//--------------------------------------------------------------------------------
// Author:   C2C Bodin
// Function: hitTop, hitBot, hitLeft, hitRight
// Purpose:  Determines if the ball position (plus or minus the radius as appropriate)
//			touches a wall. Return 1 if true and 0 if not.
//--------------------------------------------------------------------------------

char hitTop(ball_t ball){
	if(ball.position.y <= 0){
		return 1;  //True
	}

	else {
		return 0;  //False
	}
}

char hitBot(ball_t ball){
	if((ball.position.y + 1) >= SCREEN_HEIGHT){ //Because the y cursor jumps by 8 pixels
		return 1;
	}

	else {
		return 0;
	}
}

char hitLeft(ball_t ball){
	if(ball.position.x <= 0){
		return 1;
	}

	else {
		return 0;
	}
}

char hitRight(ball_t ball){
	if((ball.position.x + ball.radius) >= SCREEN_WIDTH){
		return 1;
	}

	else {
		return 0;
	}
}

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
