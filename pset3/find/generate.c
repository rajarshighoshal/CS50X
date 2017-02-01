/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Decaring the constant LIMIT(upper bound of pseudorandom no.s)
#define LIMIT 65536

int main(int argc, string argv[])
{
    // checking if command-line argument is valid or not.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // converting argv[1] to an integer n(no.s of pseudonumber to be generated)
    int n = atoi(argv[1]);

    // if argv[2] is present seeding using argv[2]; otherwise seeding randomly with time(NULL)
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // Generating n no. of pseudorandom integers, one in each line
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}