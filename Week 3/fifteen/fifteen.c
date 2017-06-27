/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}
/**
 * Greets player.
 */
void greet(void)
{

    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}


void init(void)
{
    int tile=(d*d)-1;
   
   
   // x1 defines the vertical(row), y1 the horizontal(columm)
   //Initializes the game's board with tiles numbered 1 through d*d - 1
   // Blank Tile will get value 0
     for (int x1=0; x1<d; x1++)
     {
         for (int y1=0; y1<d; y1++)
         {
             board[x1][y1]=tile;
             tile--;
         }
     }
    
    //changes 1 and 2 location if d is even
    
    if (d==4||d==6||d==8)
    {
        board[d-1][d-3]=1;
        board[d-1][d-2]=2;
    }
    
}

void draw(void)
{

// x1 defines the vertical(row), y1 the horizontal(columm)
//Prints the board in its current state. (does not print 0)
    printf("\n");
    for (int x1=0; x1<d;x1++)
    {
         for (int y1=0; y1<d;y1++)
        {
            if (board[x1][y1]!=0)
            {
            printf("%2i ", board[x1][y1]);  
            }
            else
            {
            printf("   ");    
            }
        }
        printf("\n");
    }

}


bool move(int tile)
{
   // x1 defines the vertical(row), y1 the horizontal(columm) of the requested tile
   // x2 defines the vertical(row), y2 the horizontal(collum) of the blank (0) tile
    int x1;
    int y1;
    int x2;
    int y2;
    
    // finds location of tile in array
   
     for (int searchx=0; searchx<d; searchx++)
     {
         for (int searchy=0; searchy<d; searchy++)
         {
             if (board[searchx][searchy]==tile)
            {
                x1=searchx;
                y1=searchy;
            }
         }
     }

    
    
//checking if blank tile is boarding chosen tile, and if so switching blank and chosen tile location
    
    // check top boarder for blank
   
    x2=x1-1;
    y2=y1;

    if (x2>=0)
    {
        if (board[x2][y2]==0)
        {
            board[x2][y2]=tile;
            board[x1][y1]=0;
            return true;
        }
    }
    
    //check right boarder for blank
   
    x2=x1;
    y2=y1+1;
    
        if (y2<d)
    {
        if (board[x2][y2]==0)
        {
            board[x2][y2]=tile;
            board[x1][y1]=0;
            return true;
        }
    }
    
      
      //check bottom boarder for blank
    
    x2=x1+1;
    y2=y1;
     
        if (x2<d)
    {
        if (board[x2][y2]==0)
        {
            board[x2][y2]=tile;
            board[x1][y1]=0;
            return true;
        }
    }
    
    //check left boarder for blank
    
    x2=x1;
    y2=y1-1;
 
        if (y2>=0)
    {
        if (board[x2][y2]==0)
        {
            board[x2][y2]=tile;
            board[x1][y1]=0;
            return true;
        }
    }
    
    // otherwise return false
    return false;       
}

bool won(void)
{
    
    //checker acts as counter to see if changes still need to be made to sort the array
    int checker= 100;
 
    //searchx for horizontal (row of array)
    //searchy for vertical (columm of array)
    
      for (int searchx=0; searchx<d; searchx++)
     {
         for (int searchy=0; searchy<d; searchy++)
         {
                //breaks loop if searchx+1 points boyond the array
                if (searchx+1==d)
                 {
                     break;
                 }
                 
                // if searchy+1 points outside of array
                //checks current point of array against first point on new row (board[searchx+1][0])
                // increases checker if out of order
                if(searchy+1==d)
                {
                    if (board[searchx][searchy]>board[searchx+1][0])
                    {
                    checker++;
                    }   
                }
               
               
               // checks if the next point in the array (board[searchx][searchy+1]) is the last point of the array
              // breaks loop if board[searchx][searchy+1] is 0
                if (board[searchx][searchy+1]==board[d-1][d-1])
                 {
                     if (board[searchx][searchy+1]==0)
                     {
                         break;
                     }
                    
                 }
                 
                 
                //increases checker if array points not sorted 
                if (board[searchx][searchy]>board[searchx][searchy+1])
                {
                checker++;
                }
         }
     }
     
    //if checker has not changed, confirm WON is true
    if (checker==100)
    {
        return true;
    }
    // else won is false
    return false;
}
