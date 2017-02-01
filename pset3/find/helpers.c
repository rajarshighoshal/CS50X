/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n <= 0)
    {
        return false;
    }
    // Binary search
    
    //declaring start end and mid variables
    int start, end, mid;
    start = 0;
    end = n-1;
    mid = (start + end)/2;
    
    //delaring working array and getting values for it
    int *working = malloc(sizeof(int)*n);
    for(int  i  = 0; i < n; i++)
    {
        working[i] = values[i];
    }
    
    //looping
    do
    {
        //if digit is matched
        if(value == working[mid])
        {
            //success
            return true;
        }
        //if digit is greater than mid num
        else if(value > working[mid])
        {
            start = mid + 1;
            mid = (start + end)/2;
        }
        //if digit is less than mid num
        else if(value < working[mid])
        {
            end = mid - 1;
            mid = (start + end)/2;
        }
    }
    //checking condition
    while(end >= start);
    
    
    //failure
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //Bubble sort
    //introducing & initializing swap variable 
    int swap_count = -1;
    while(swap_count != 0)
    {
      //setting value of swap variable to zero
      swap_count = 0;
      for(int i = 0; i < n-1; i++)
      {
        // comparing values in the array
        if(values[i] > values[i+1])
        {
            //swapping if necessary
            int temp = values[i];
            values[i] = values[i+1];
            values[i+1] = temp;
            //incrementing swapping variable
            swap_count++;
        }
      }
    }  
    return;
}