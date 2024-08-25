/*
 * INTEGER SQUARE ROOT
 * written by \u5C0F\u6797\u79C0\u884C
 *
 * References:
 * - https://en.wikipedia.org/wiki/Integer_square_root
 * - https://www.nist.gov/dads/HTML/squareRoot.html
 * - isbn-13:978-0-321-84268-8
 */

#include "sqrt32.h"

unsigned long int sqrt32(unsigned long int square)
{
	unsigned long int bit, root = 0uL;

	for (bit = (1uL << (040 - 2)); bit != 0uL; bit >>= 2) {
		unsigned long int delta = root | bit;

		root >>= 1;

		if (square >= delta) {
			square -= delta;
			root |= bit;
		}
	}

	return root;
}
