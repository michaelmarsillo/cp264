/*
--------------------------------------------------
Project: a5q3
File:    bigint.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

/*
 * Creates and returns BIGINT object by converting the digit string.
 */

BIGINT bigint(char *p) {
  BIGINT bn = {0};
  if (p == NULL)
    return bn;
  else if (!(*p >= '0' && *p <= '9')) {// not begin with digits
    return bn;
  }
  else if (*p == '0' && *(p+1) == '\0') {// just "0"
    dll_insert_end(&bn, dll_node(*p -'0'));
    return bn;
  }
  else {
    while (*p) {
      if (*p >= '0' && *p <= '9' ){
        dll_insert_end(&bn, dll_node(*p -'0'));
      } else {
        dll_clean(&bn);
        break;
      }
      p++;
    }
    return bn;
  }
}

/*
 * Add two BIGINT operants and returns the sum in BIGINT type.
 * @param oprand1  - first operand of BIGINT type.
 * @param oprand2  - second operand of BIGINT type.
 * @return - the sum of oprand1 and oprand2 in BIGINT type.
 */

BIGINT bigint_add(BIGINT op1, BIGINT op2) {
// your code
	BIGINT result = {0};
	    int carry = 0;

	    NODE *n1 = op1.end;
	    NODE *n2 = op2.end;

	    while (n1 || n2 || carry) {
	        int sum = carry;

	        if (n1) {
	            sum += n1->data;
	            n1 = n1->prev;
	        }
	        if (n2) {
	            sum += n2->data;
	            n2 = n2->prev;
	        }

	        carry = sum / 10;
	        sum %= 10;

	        dll_insert_start(&result, dll_node(sum));
	    }

	    return result;

}


/*
 * Compute and return Fibonacci(n)
 * @param n - input positive integer
 * @return  - Fibonacci(n) in BIGINT type
 */

BIGINT bigint_fibonacci(int n) {
// your code
	 if (n == 0) return bigint("0");
	    if (n == 1) return bigint("1");

	    BIGINT prev = bigint("0");
	    BIGINT curr = bigint("1");

	    for (int i = 2; i <= n; i++) {
	        BIGINT temp = bigint_add(prev, curr);
	        dll_clean(&prev);
	        prev = curr;
	        curr = temp;
	    }

	    dll_clean(&prev);
	    return curr;
}
