#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


double twoDecs(double n)
{
    return (int)(n*100)/100.0;
}

char* Prob538(double target, int n)
{
    int i, j, closesti = 1, closestj = 1, iter = 0;
    double closest = 1;
    target/=100;        // to put in range 0 to 1

    //printf("\n%lf", target);

    for(i=1;i<=n;i++)
    {
        for(j=1;j<i;j++)
        {
            //TODO: remove checking redundant fractions like 2/4, 3/9 by checking if mod 1 of i/j (yes i/j, not j/i) != 0
            printf("\n %d/%d", j, i);


            if(fabs(target - (double)j/i) < fabs(target - closest))
            {
                printf("(New closest)");

                closestj = j;
                closesti = i;
                closest = (double)j/i;
            }

            iter++;
        }
    }

    printf("\nOriginal version took %d iterations  (%d in %d odds) \n", iter, closestj, closesti);
    iter=0;

    j=1;
    bool needsDecr = false, higher = false;      //higher referring to the *target* value being higher than the current one
    double diff;

    for(i=1;i<=n;i++)
    {
        printf("\nOuter loop: %d/%d", j, i);

        diff = target - (double)j/i;

        higher = diff > 0 ? true : false;

        if (fabs(diff) < fabs(target - closest))
        {
            closestj = j;
            closesti = i;
            closest = (double) j / i;
        }





        for(;higher;)
        {
           j++;        //here instead of end of loop because even when it already went over the target, it would still increment
                       //meaning it would always increment one too many times

            printf("\nInner Loop: %d/%d", j, i);

            diff = target - (double)j/i;

            higher = diff > 0 ? true : false;

            if(fabs(target - (double)j/i) < fabs(target - closest))
            {
                closestj = j;
                closesti = i;
                closest = (double)j/i;
            }

            needsDecr = true;
            iter++;
        }                   //can't currently guarantee same outcome as original inefficient version.
                        //TODO: Create a check for that then run so many tests

        //if(needsDecr)
          //  j--;

        iter++;

    }

    printf("\nAlternative  version took %d iterations\n", iter);


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
        /*int num = rand();

        printf("\nTime = %d", (unsigned int)time(NULL));
        printf("\nRand Num: %d", num);

        double newNum = (double) (num % 10000) / 100;       //to put in form xx.yy  e.g. 73.56%
        printf("\n%.2lf%%", newNum);*/

        printf("\n%s \n", Prob538(33.56, 10));
    }
    return 0;
}