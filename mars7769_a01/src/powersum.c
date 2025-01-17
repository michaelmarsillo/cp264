/*
--------------------------------------------------
Project: a1q2
File:    powersum.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/



#include "powersum.h"

/**
 * Detect if overflow in power computing of b to power of n
 *
 * @param b - the base
 * @param n - the exponent
 * @return - 1 if overflow happens, 0 otherwise
 */
int power_overflow(int b, int n) {
	int p = 1;

	    for (int i = 1; i <= n; i++) {
	        int temp = p * b;
	        if (temp / b != p) {
	            return 1;
	        }
	        p = temp;
	    }

	    return 0;
	}

/**
 * Compute and return b to power of n.
 *
 * @param b - the base
 * @param n - the exponent
 * @return - b to the power of n if no overflow happens, 0 otherwise
 */
int mypower(int b, int n) {
    int p = 1;

    for (int i = 1; i <= n; i++) {
        int temp = p * b;
        if (temp / b != p) {
            return 0;
        }
        p = temp;
    }

    return p;
}


/**
 * Compute and return the sum of powers.
 *
 * @param b - the base
 * @param n - the exponent
 * @return -  the sum of powers if no overflow happens, 0 otherwise
 */
int powersum(int b, int n) {
   int p = 1;
   int sum =1;

   for (int i = 1; i <= n; i++) {
	   int temp = p*b;
	   if ((temp/b) != p) {
		   return 0;
	   } else {
		   p = temp;
	   }

	   if ((sum + p) < sum) {
		   return 0;
	   }
	   sum +=p;
   }
   return sum;
}

