#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


int main(void)
{
    int i, j, turns;
    int fullMatch, partialMatch;
    bool won = false;
    bool MaxColoursAltered = false;
    char userInput;

    int MaxPegs = 4;
    int MaxTurns = 12;
    int MaxColours = 8;


    srand((unsigned int) time(NULL)); // randomize seed

    //(unsigned int) is included to avoid a warning about incidentally casting a type time_t to unsigned int

    printf("If you wish to alter the default number of pegs, turns, or colours, press 1, 2, or 3 respectively. \nFor none of these, press 0.\n");

    while((userInput = getchar())!='0')    //or some other way?
    {
        switch(userInput)
        {
            case '1':
                printf("\nThe current number of pegs per code is 4. What would you like to change it to?\n");
                scanf("%d", &MaxPegs);
                break;

            case '2':   printf("\nThe current maximum number of turns per game is 12. What would you like to change it to?\n");
                scanf("%d", &MaxTurns);
                break;

            case '3':   printf("\nThe default number of colours is 8. What would you like to change it to?\n");
                scanf("%d", &MaxColours);
                MaxColoursAltered = true;

                if(MaxColours>8)
                {
                    printf("\nSince the number you have provided is bigger than the defualt of eight,"
                           "you'll have to provide the names of additional colours.\n");



                }
                break;

            default: printf("\nThat was not a valid option\n");
        }

        printf("\nIf you wish to alter the default number of pegs, turns, or colours, press 1, 2, or 3 respectively. \nFor none of these, press 0.\n");

    }

    typedef struct {                //declared here so that values can be altered by user first
        char guess[MaxPegs];        //need to use malloc to get around struct VLA incompatibility?
        int fullMatch;
        int partialMatch;
    }TurnDetails;


    printf("\nThe guessable colours will be purple, magenta, red, orange, yellow, white, blue, and green");
    //only because these are the ones on my own physical version of the game

    printf("%s", MaxColoursAltered?"plus any others you've added.\n":".\n");

    printf("Each are represented by their unique first letter. Capitalisation doesn't matter.\n");

    //optional: feature that lets player add in more colour possibilities       probably involves malloc?
    //automatically change max turns based on this?

    //create arrays, 1ds and 2d
    char code[MaxPegs];
    char guess[MaxPegs];
    int fullMatchPosition[MaxPegs];
    int partialMatchPosition[MaxPegs];

    TurnDetails prevTurns[MaxTurns];

    char *colourList[]={"green", "blue", "purple", "red", "magenta", "orange", "yellow", "white"};   //still need to doublecheck if these are the real colours

    //player colours are added to either existing ones or new empty set, depending on preference expressed
    //simplest to keep existing array as is and use additional one for new colours
    //need to check with existing array and other new colours to make sure no two first letters are the same
    //maybe simpler to only record first letters?


    //initalise all to blanks

    for(i=0; i<MaxTurns; i++)
    {
        prevTurns[i].fullMatch = 0;
        prevTurns[i].partialMatch = 0;

        for(j=0; j<MaxPegs; j++)
        {
            prevTurns[i].guess[j] = ' ';
        }
    }

    //take input for code and store in 1d array

    printf("\nDo you want to input a specific code? y/n? If not, one will be randomly generated for you.\n");
    scanf(" %c", &userInput);

    if(userInput=='y'||userInput=='Y')
    {
        printf("Please set your 4-colour code\n");
        scanf(" %c %c %c %c", &code[0], &code[1], &code[2], &code[3]);

        printf("\nYour code was: %c %c %c %c", code[0], code[1], code[2], code[3]);
    }
    else if(userInput=='n'||userInput=='N')
    {
        for(i=0; i<MaxPegs;i++)
        {
            int colourNum = rand()%MaxColours;
            code[i] = *colourList[colourNum];
        }
    }
    else
    {
        printf("Invalid response. Please try again using 'y' or 'n'.");
        return 0;       //change to while loop until valid input
    }

    for(turns=0; turns<MaxTurns && !won; turns++)
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

        for(i=0; i<MaxPegs; i++)
        {
            //if so, record position and quantity of matches
            if(guess[i]==code[i])
            {
                fullMatchPosition[fullMatch++] = i;
            }
        }


        //check for partial matches

        partialMatch = 0;

        for(i=0; i<MaxPegs; i++)
        {
            for(j=0; j<MaxPegs; j++)
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


            for(j=0; j<MaxPegs; j++)
            {
                printf("%c ", prevTurns[i].guess[j]);
            }
        }

        if(fullMatch == 4)
        {
            won = true;
        }

    }

    if(won)
    {
        printf("\n\nCongratulations! You won!\n");
    }
    else
    {
        printf("\n\nBetter luck next time.\n");
    }

    printf("The code was: %c %c %c %c\n", code[0], code[1], code[2], code[3]);

    return 0;
}