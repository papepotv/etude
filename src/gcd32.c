/*
 * GREATEST COMMON DIVISOR
 * written by \u5C0F\u6797\u79C0\u884C
 *
 * References:
 * - https://en.wikipedia.org/wiki/Binary_GCD_algorithm
 */

#include "gcd32.h"

unsigned long int gcd32(unsigned long int u, unsigned long int v)
{
	int w;

	if (u == 0uL || v == 0uL) {
		return u | v;
	}

	for (w = 0; ((u | v) & 1uL) == 0uL; w++) {
		u >>= 1;
		v >>= 1;
	}

	while ((u & 1uL) == 0uL) {
		u >>= 1;
	}

	while ((v & 1uL) == 0uL) {
		v >>= 1;
	}

	while (u != v) {
		if (u > v) {
			u -= v;
			do {
				u >>= 1;
			} while ((u & 1uL) == 0uL);
		} else {
			v -= u;
			do {
				v >>= 1;
			} while ((v & 1uL) == 0uL);
		}
	}

	return u << w;
}
