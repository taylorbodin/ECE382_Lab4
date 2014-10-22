/*
 * pong.h
 * Author: Todd Branchflower
 * Date: 11 Oct 2013
 * Description: Implements a subset of the pong game
 * Updated 10/14/14 by C2C Bodin
 */

#ifndef _PONG_H
#define _PONG_H

#define SCREEN_WIDTH 12
#define SCREEN_HEIGHT 9

typedef struct {
    int x;
    int y;
} vector2d_t;

typedef struct {
    vector2d_t position;
    vector2d_t velocity;
    unsigned char radius;
} ball_t;

ball_t createBall(int xPos, int yPos, int xVel, int yVel, unsigned char radius);

ball_t moveBall(ball_t ballToMove);

char hitTop(ball_t ball);

char hitBot(ball_t ball);

char hitLeft(ball_t ball);

char hitRight(ball_t ball);

void Sleep(int ms);

int getX(ball_t ball);

int getY(ball_t ball);

#endif
