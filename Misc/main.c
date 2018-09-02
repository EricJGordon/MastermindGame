#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


double twoDecs(double n)
{
    return (int)(n*100)/100.0;
}

double rand2dot2(bool printDetails)
{

    int num = rand();

    double doubleNum = (double) (num % 10000) / 100;       //to put in form xx.yy  e.g. 73.56%

    if(printDetails)
    {
        printf("\nTime = %d", (unsigned int) time(NULL));
        printf("\nRand Num: %d", num);
        printf("\n%.2lf%%", doubleNum);
    }

    return doubleNum;
}

int gcd(int a, int b)       //courtesy of Stack Overflow
{                           //needed for Prob538
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

char* Prob538(double target)
{
    int i, j, closesti = 1, closestj = 1, iter = 0;
    double closest = 1;
    target/=100;        // to put in range 0 to 1


    //Following 3 variables are all tweakable depending on personal preference
    int limit = 10;     //highest denominator for initial stage
    double MOE = 0.004;   //i.e. 0.4%          only applies to chances over 90% or less than 10%
    int HighestX5 = 25;     //Highest multiple of 5 used as denominator (after 'limit' is reached) before switching to multiples of 10


    for(i=1;i<=limit;i++)
    {
        for(j=1;j<i;j++)
        {
            printf("\n %d/%d", j, i);

            if(i==1&&j==1)
                printf("Print, Damn you!");       //why isn't this triggering/isn't 1/1 being printed above?


            if(gcd(i,j)==1 && fabs(target - (double)j/i) < fabs(target - closest))
            {                                  //first condition to avoid checking (and changing answer to)
                printf("(New closest)");       //redundant fractions like 2/4, 3/9, 8/10
                                               //i.e. any numerator and denominator that aren't relatively prime
                closestj = j;
                closesti = i;
                closest = (double)j/i;
            }

            iter++;
        }
    }


    for(i=10; fabs(target - closest)>MOE && (target>0.9||target<0.1) && i<=100 ; i+=(i<=HighestX5?5:10))
    {
        for(j=1;j<i;j++)
        {
            printf("\n %d/%d", j, i);

            if(gcd(i,j)==1 && fabs(target - (double)j/i) < fabs(target - closest))
            {                                  //first condition to avoid checking (and changing answer to)
                printf("(New closest)");       //redundant fractions like 2/4, 3/9, 8/10
                                                //i.e. any numerator and denominator that aren't relatively prime
                closestj = j;
                closesti = i;
                closest = (double)j/i;
            }

            iter++;
        }

    }

    printf("\n\nTarget = %.2lf%%\nCurrent = %d/%d a.k.a %.2lf%%\nDiff = %.2lf%%\n", target*100, closestj, closesti, (double)closestj/closesti*100, fabs(target - (double)closestj/closesti)*100);
    printf("%.2lf%% < %.2lf%% MOE : %s\n", fabs(target - (double) closestj / closesti)*100, MOE*100 , fabs(target - (double) closestj / closesti) < MOE ? "True" : "False");

    int origJ = closestj, origI = closesti;
    printf("\nOriginal version took %d iterations  (%d in %d odds) \n", iter, closestj, closesti);

    closesti = 1, closestj = 1, iter=0, closest=1, j=1; //reset so that original algorithm's changes don't affect results

    bool tooLow;      //tooLow referring to the *current* value being lower than the target one
    double diff;

    for(i=1;i<=limit;i++)
    {
        printf("\nOuter loop: %d/%d", j, i);

        diff = target - (double)j/i;

        tooLow = diff > 0 ? true : false;

        if (gcd(i,j)==1 && fabs(diff)<fabs(target-closest))
        {
            printf(" \t(New closest)");

            closestj = j;
            closesti = i;
            closest = (double) j / i;
        }





        while(tooLow&&i<10)     //&&i<10 to prevent cases where it gives the final fraction out of a higher number
                                //as a result, such as 73.66% giving 8 in 11 instead of 3 in 4
        {
           j++;
           i++;

            printf("\n Inner Loop: %d/%d", j, i);

            diff = target - (double)j/i;

            tooLow = diff > 0 ? true : false;

            if(gcd(i,j)==1 && fabs(diff)<fabs(target-closest))
            {
                printf(" \t(New closest)");

                closestj = j;
                closesti = i;
                closest = (double)j/i;
            }

            iter++;
        }

        iter++;

    }

    printf("\nAlternative  version took %d iterations\n", iter);

    if (origI!=closesti || origJ != closestj)
    {
        printf("\nERROR\nERROR\nERROR\nERROR\nERROR\nERROR\nERROR");
    }


    //TODO: Add final feature of expressing fractions that need more precision than a denominator of 10 can offer
    //e.g. 6.58% , 97.51%, not by extending the denominator of 10 to 11, 12 so on, but by testing neater denominators
    //of multiples of certain numbers, such as of 5s or 10s, which would give probabilities of 1 in 15, and 39 in 40
    //for the two examples mentioned

    unsigned int buffersize = 13 ;
    char* buffer = malloc(buffersize);

     snprintf(buffer, buffersize, "%d in %d odds", closestj, closesti);
     //printf("\n%d in %d odds", closestj, closesti);

    return buffer;
}



int main(void)
{
    srand((unsigned int)time(NULL));

    while(getchar())        //as opposed to running the whole program multiple times because then it wasn't random enough
    {
        printf("\n%s \n", Prob538(rand2dot2(1)));
    }

    return 0;
}