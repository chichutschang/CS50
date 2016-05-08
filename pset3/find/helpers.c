/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 * Chi-Chu Tschang
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    // implement a searching algorithm: binary search

            {
            int first = 0;
            int last = n-1;
            
            while (first <= last)
            {
                int middle = (first + last) / 2; 
                
                if (values[middle]==value)
                {
                    return true;
                }
                
                else if (values[middle] > value)
                {   
                    last = middle - 1;
                }
                   
                else if (values[middle] < value)
                {
                    first = middle + 1;
                }                       
                }
            }  
        return false;
}
/**
 * Sorts array of n values.
 */
 void sort(int values[], int n)
{
    // implement an O(n^2) sorting algorithm: bubble sort

            for (int i = 0; i < n-1; i++)
            {
                if (values[i] > values[i+1])
                {
                    int temp = values[i];
                    values[i] = values[i+1];
                    values[i+1] = temp;
                }   
            }
           
}

