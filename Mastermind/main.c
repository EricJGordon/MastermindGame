#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_COLOURS 4
#define MAX_TURNS 12

typedef struct {
    char guess[MAX_COLOURS];
    int fullMatch;
    int partialMatch;
}Record;


int main(void)
{
    int i, j, turns;
    int fullMatch, partialMatch;
    bool won = false;
    char userInput;


    //colours are green blue red pink orange yellow white,
    //each represented by their own unique first letter,
    //Instruct player this

    //optional: feature that lets player add in more colour possibilities
    //automatically change max turns based on this?

    //create arrays, 1ds and 2d
    char code[MAX_COLOURS];
    char guess[MAX_COLOURS];
    int fullMatchPosition[MAX_COLOURS];
    int partialMatchPosition[MAX_COLOURS];

    Record prevTurns[MAX_TURNS];


    //initalise all to blanks

    for(i=0; i<MAX_TURNS; i++)
    {
        prevTurns[i].fullMatch = 0;
        prevTurns[i].partialMatch = 0;

        for(j=0; j<MAX_COLOURS; j++)
        {
            prevTurns[i].guess[j] = ' ';
        }
    }

    //take input for code and store in 1d

    printf("Do you want to input a specific code? y/n? If not, one will be randomly generated for you.\n");
    scanf("%c", &userInput);

    if(1/*userInput=='y'||userInput=='Y'*/)
    {
        printf("Please set your 4-colour code\n");
        scanf(" %c %c %c %c", &code[0], &code[1], &code[2], &code[3]);

        printf("\nYour code was: %c %c %c %c", code[0], code[1], code[2], code[3]);
    }


    for(turns=0; turns<MAX_TURNS && won == false; turns++)
    {

        //take input for guess and store in 1d

        printf("\n\nPlease input your %s guess\n", turns==0?"first":"next");
        scanf(" %c %c %c %c", &guess[0], &guess[1], &guess[2], &guess[3]);

        //printf("\nYour guess was: %c %c %c %c\n", guess[0], guess[1], guess[2], guess[3]);


        //determine accuracy of guess

        fullMatchPosition[0] = -1;	//initialise arrays
        fullMatchPosition[1] = -1;	//-1 just because it's not a number that could occur naturally
        fullMatchPosition[2] = -1;
        fullMatchPosition[3] = -1;

        partialMatchPosition[0] = -1;
        partialMatchPosition[1] = -1;
        partialMatchPosition[2] = -1;
        partialMatchPosition[3] = -1;

        //first check if complete match,

        fullMatch = 0;

        for(i=0; i<MAX_COLOURS; i++)
        {
            //if so, record position and quantity of matches
            if(guess[i]==code[i])
            {
                fullMatchPosition[fullMatch++] = i;
            }
        }


        //check for partial matches

        partialMatch = 0;

        for(i=0; i<MAX_COLOURS; i++)
        {
            for(j=0; j<MAX_COLOURS; j++)
            {
                if(guess[i]==code[j]						//compares all to all by default
                   &&j!=fullMatchPosition[0]&&j!=fullMatchPosition[1]&&j!=fullMatchPosition[2]&&j!=fullMatchPosition[3]			//exclude previously recorded full matches
                   &&i!=fullMatchPosition[0]&&i!=fullMatchPosition[1]&&i!=fullMatchPosition[2]&&i!=fullMatchPosition[3]
                   &&j!=partialMatchPosition[0]&&j!=partialMatchPosition[1]&&j!=partialMatchPosition[2]&&j!=partialMatchPosition[3]//and already recorder partial matches
                        )																												//to prevent them from being double counted
                {
                    partialMatchPosition[partialMatch++] = j;

                    break;	// so that it correctly stops after finding the first instance of the same colour
                    //i.e. so one guess peg can't match with multiple code pegs of the same colour

                    //could presumably also be achieved by adding a 4th line to the above if statement
                    //along the lines of &&i!=partialMatchPosition2[0]&&i!=partialMatchPosition2[1]...
                    //where this second array is filled similar to the first but replacing j for i

                }
            }
        }

        //add previous guess to 2d array/structs

        prevTurns[turns].guess[0] = guess[0];
        prevTurns[turns].guess[1] = guess[1];
        prevTurns[turns].guess[2] = guess[2];
        prevTurns[turns].guess[3] = guess[3];

        //and other data

        prevTurns[turns].fullMatch = fullMatch;
        prevTurns[turns].partialMatch = partialMatch;

        //print results

        for(i=0; i<=turns; i++)
        {
            printf("\nFull = %d   Partial = %d\t\t", prevTurns[i].fullMatch, prevTurns[i].partialMatch);


            for(j=0; j<MAX_COLOURS; j++)
            {
                printf("%c ", prevTurns[i].guess[j]);
            }
        }

        if(fullMatch == 4)
        {
            won = true;
        }

    }

    if(won==true)
    {
        printf("...");
    }
    else
        printf("...");

    return 0;
}