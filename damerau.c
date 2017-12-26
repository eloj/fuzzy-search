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

#define MIN2(A, B) ((A)<(B) ? (A) : (B))
#define MIN3(A, B, C) ((A) < (B) ? MIN2(A, C) : MIN2(B, C))

/*
	Unrestricted Damerau-Levenshtein Edit Distance. O(m*n) time, O(m*n+|Σ|) space.

	NOTE: This is NOT the 'Optimal String Alignment' / 'Restricted Edit Distance'
	function.
*/
static int damerau_ref(const char *A, int m, const char *B, int n) {
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

	int C[m+1][n+1];
	int CP[256] = { 0 }; // alphabet size

	for (int i=0 ; i <= m ; ++i) C[i][0] = i;
	for (int j=0 ; j <= n ; ++j) C[0][j] = j;

	for (int i=1 ; i <= m ; ++i) {
		int CS = 0;
		for (int j=1 ; j <= n ; ++j) {
			int d = (A[i-1] != B[j-1]) ? 1 : 0;
			C[i][j] = MIN3(C[i-1][j] + 1, C[i][j-1] + 1, C[i-1][j-1] + d);
			int ip = CP[(unsigned int)B[j-1]];
			int jp = CS;
			if (ip > 0 && jp > 0) {
				// Update with min of current distance or the transpose.
				C[i][j] = MIN2(C[i][j], C[ip-1][jp-1] + (i-ip) + (j-jp) - 1);
			}
			if (!d)
				CS = j;
		}
		CP[(unsigned int)A[i-1]] = i;
	}

	return C[m][n];
}

#ifndef NO_MAIN
int main(int argc, char *argv[])
{
	const char *s1 = argc > 1 ? argv[1] : "CA";
	const char *s2 = argc > 2 ? argv[2] : "ABC";

	int d = damerau_ref(s1, -1, s2, -1);

	printf("damerau('%s', '%s') = %d\n", s1, s2, d);

	return EXIT_SUCCESS;
}
#endif
