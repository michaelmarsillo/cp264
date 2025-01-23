/*
--------------------------------------------------
Project: a2q1
File:    fibonacci.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include "fibonacci.h"

/**
 * Cmpute and return the nth Fibonacci number F(n) using iterative algorithm,
 *  namely using a for or while loop.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int iterative_fibonacci(int n) {
// your implementation
	if (n == 0) return 0;
	if (n == 1) return 1;

	int prev1= 0;
	int prev2= 1;
	int current;
	for (int i = 2; i <=n; i++){
		current = prev1 + prev2;
		prev1 = prev2;
		prev2 = current;

	}
	return current;


}

/**
 * Cmpute and return the nth Fibonacci number F(n) using recurisve algorithm,
 *  namely using recursion function.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int recursive_fibonacci(int n) {
// your implementation
	if (n == 0) return 0;
	if (n == 1) return 1;

	return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);


}


/**
 * Cmpute and return the nth Fibonacci number F(n) using dynamic programming
 * bottom-up method with external array f[n+1] of initial value -1 for all elements.
 * Namely it fills up f[] byf[0]=0, f[1]=1, a[i]= a[i-2]+a[i-1] for i=2,...,n, and
 * return f[n].
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int dpbu_fibonacci(int *f, int n) {
// your implementation
	f[0] = 0;
	if (n > 0) f[1] = 1;

	for (int i = 2; i <= n; i++) {
	   f[i] = f[i - 1] + f[i - 2];
	}
	return f[n];

}

/**
 * Cmpute and return the nth Fibonacci number F(n) using dynamic programming
 * top-down method with external array f[n+1] of initial value -1 for all elements.
 * Namely it fills up f[n+1] by recursion function call. Specifically it returns
 * f[n] if f[n]>0 else sets f[n] = dptd_fibonacci(f, n-2) + dptd_fibonacci(f, n-1)
 * and then returns f[n]
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number F(n).
 */
int dptd_fibonacci(int *f, int n) {
// your implementation
	if (n == 0) return 0;
	if (n == 1) return 1;

	if (f[n] != -1) {
		return f[n];
	}
	f[n] = dptd_fibonacci(f, n -1) + dptd_fibonacci(f, n -2);
	return f[n];
}
