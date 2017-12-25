/*
MIT License

Copyright (c) 2017 Eddy L O Jansson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Levenshtein Edit Distance. O(m*n) time, O(m) space.

	When max_k is < 0, the true distance is returned.

	When max_k is > 0, the algorithm will only return the real
	distance if it's less or equal to max_k, else a distance of
	at least max_k is returned.

	Using a max_k of 0 doesn't make much sense.
*/
static int levenshtein(const char *A, int m, const char *B, int n, int max_k) {
	if (m < 0)
		m = strlen(A);
	if (n < 0)
		n = strlen(B);
	if (m == 0)
		return n;
	if (n == 0)
		return m;

	// Swap so that m <= n, for the inner loop.
	if (n < m) {
		const char *t = A;
		A = B;
		B = t;
		int tl = m;
		m = n;
		n = tl;
	}

	if (max_k < 0)
		max_k = n;
	/*
	else if (max_k == 0 && m == n)
		return strncmp(A, B, m) == 0 ? 0 : 1;
	*/
	else if (n - m >= max_k)
		return max_k;

	// This will store d_{0,j}..d_{i-1,j} | d_{i,j-1}..d_{m,j-1}
	// i.e even more compact than storing two full rows.
	int C[m + 1];

	for (int i=0 ; i <= m ; ++i)
		C[i] = i;

	for (int j=1 ; j <= n ; ++j) {
		int c = C[0]; // c tracks d_{i-1,j-1}
		C[0] = j;

		// Restrict to 2*(max_k + 1) wide window, from max(1, j - max_k - 1) to min(m, j + max_k + 1)
		int w0 = (j - max_k - 1) > 1 ? (j - max_k - 1) : 1;
		int w1 = (j + max_k - 1) < m ? (j + max_k - 1) : m;
		// In the base case, i=1 to m
		for (int i=w0 ; i <= w1 ; ++i) {
			int d0 = (A[i-1] != B[j-1] ? 1 : 0) + c;
			int d1 = C[i-1] + 1;
			int d2 = C[i] + 1;
			// d = min3(d0, d1, d2);
			int m0 = d0 < d1 ? d0 : d1;
			int d = m0 < d2 ? m0 : d2;
			c = C[i];
			C[i] = d; // d_{i,j}
		}
	}

	return C[m];
}

#ifndef NO_MAIN
int main(int argc, char *argv[])
{
	int max_k = argc > 1 ? atoi(argv[1]) : -1;
	const char *s1 = argc > 2 ? argv[2] : "volkswagen";
	const char *s2 = argc > 3 ? argv[3] : "folkvagnen";

	int d = levenshtein(s1, -1, s2, -1, max_k);

	int exact = (max_k < 0 || d < max_k);
	printf("ed('%s', '%s', %d) %s %d\n", s1, s2, max_k, exact ? "=" : "at least", exact ? d : max_k);

	return EXIT_SUCCESS;

}
#endif
