#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double twoDecs(double n)
{
    return (int)(n*100)/100.0;
}

char* Prob538(double target, int n)
{
    int i, j, closesti = 1, closestj = 1;
    double closest = 1;
    target/=100;        // to put in range 0 to 1

    //printf("\n%lf", target);

    for(i=1;i<=n;i++)
    {
        for(j=1;j<i;j++)
        {
            //TODO: remove checking redundant fractions like 2/4, 3/9 by checking if mod 1 of i/j (yes i/j, not j/i) != 0

            if(fabs(target - (double)j/i) < fabs(target - closest))
            {
             //     printf("\n%d/%d", j, i);
             closestj = j;
             closesti = i;
             closest = (double)j/i;
            }

        }

    }


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
        int num = rand();

        printf("\nTime = %d", (unsigned int)time(NULL));
        printf("\nRand Num: %d", num);

        double newNum = (double) (num % 10000) / 100;       //to put in form xx.yy  e.g. 73.56%
        printf("\n%.2lf%%", newNum);

        printf("\n%s \n", Prob538(newNum, 10));
    }
    return 0;
}