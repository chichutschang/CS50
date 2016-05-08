//
// breakout.c
//
// Computer Science 50
// Problem Set 3
// Chi-Chu Tschang

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    //click the mouse to start the game
    waitForClick();
    
    // initial velocity
    double velocityX = drand48();
    double velocityY = 1;

    //initial location of ball
    double x = (WIDTH - RADIUS)/2;
    double y = (HEIGHT - RADIUS)/2;
          
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {        
        //displays scoreboard
        updateScoreboard(window, label, points);
        
        //controls paddle
        
        //move paddle with mouse
        GEvent MovePaddle = getNextEvent(MOUSE_EVENT);
        // if we heard one
        if (MovePaddle != NULL)
            {
            // if the paddle moves
            if (getEventType(MovePaddle) == MOUSE_MOVED)
                {
                    // ensure paddle moves sideways
                    double x = getX(MovePaddle) - getWidth(paddle) / 2;
                    double y = 500;
                    setLocation(paddle, x, 500);
                }
            }
          
          // move ball along x-axis + y-axis
          move(ball, velocityX, velocityY);
                
          // bounce off right edge of window
          if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                velocityX = -velocityX;                        
            }

          // bounce off left edge of window
          else if (getX(ball) <= 0)
            {   
                velocityX = -velocityX;   
            }        

          //bounce off bottom of window
          else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
               setLocation(ball, x, y);
               setLocation(paddle, x, 500);
               lives--;
               waitForClick();
            }

          //bounce off top of window
          else if (getY(ball) <=0)
            {
                velocityY = -velocityY;              
            }

        GObject object = detectCollision(window, ball);        
        if (object != NULL)
            {
                if (object == initPaddle)
                {
                    velocityY = -velocityY;
                }
            
                if (strcmp(getType(object), "GRect") == 0)
                {
                    velocityY = -velocityY;
                    
                    if(object != paddle)
                    {
                        removeGWindow(window, object);
                        points++;
                    }
                }
            
    if(points==50)
    {
        GLabel label=newGLabel("BREAKOUT!");
        setFont(label,"Arial-30");
        setColor(label,"#FF0054");       
        double x = 111;
        double y = 191;
        setLocation(label,x,y);
        add(window,label);
    }
    else if (lives == 0)
    {
        GLabel label=newGLabel("BETTER LUCK NEXT TIME");
        setFont(label,"Arial-30");
        setColor(label,"#FF0054");       
        double x = 9;
        double y = 191;
        setLocation(label,x,y);
        add(window,label);
    }   

            
            }
                           
        //slows down velocity of ball      
        pause(10);
    }       

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // sets wall @ y = 50px
    int block_y = 50;
    // set width of block @ 38px
    int blockwidth = 38;
    // set height of block @ 11px
    int blockheight = 11; 
    //for every row
    for (int r = 0; r < ROWS; r++)
    {
        //sets wall @ x = 2px
        int block_x = 2;
        //for every column
        for (
        int c = 0; c < COLS; c++)
        {
            //for each block
            GRect block = newGRect(block_x,block_y,blockwidth,blockheight);
            //sets color of first row from top
            if( r == 0)
                {
                setColor(block, "#390099");
                }
            //sets color of second row from top
            if( r == 1)
                {
                setColor(block, "#9E0059");
                }    
            //sets color of third row from top
            if( r == 2)
                {
                setColor(block, "#FF0054");
                } 
            //sets color of fourth row from top
            if( r == 3)
                {
                setColor(block, "#FF5400");
                }    
            //sets color of fifth row from top
            if( r == 4)
                {                
                setColor(block, "#FFBD00");
                }
        setFilled(block, true);            
        add(window, block);        
        //repeats row of block
        block_x = block_x + 40;
        } 
    //repeats column of block    
    block_y = block_y + 13;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate ball
    GOval ball = newGOval(((WIDTH - RADIUS)/2), ((HEIGHT - RADIUS)/2), RADIUS, RADIUS);
    setColor(ball, "#FF0054");
    setFilled(ball, true);
    add(window, ball);

    //initial location of ball
    double x = (WIDTH - RADIUS)/2;
    double y = (HEIGHT - RADIUS)/2;
    setLocation(ball, x, y); 
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // instatiate paddle 
    GRect paddle = newGRect(175, 500, 50, 10);
    //set color of paddle
    setFilled(paddle, true);
    setColor(paddle, "#390099");
    // add paddle to window
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // scoreboard
    GLabel label = newGLabel(""); 
    setFont(label, "Arial-30");
    setColor(label, "#D3D3D3");
    double x = 191;
    double y = 291;
    setLocation(label, x, y);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
