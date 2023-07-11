/*
 * GRAY CODE
 * written by \u5C0F\u6797\u79C0\u884C
 *
 * References:
 * - https://en.wikipedia.org/wiki/Gray_code
 * - isbn-13:978-0-321-84268-8
 */

#include "graycode.h"

unsigned long int engray32(unsigned long int u)
{
	u ^= (u >> 001);

	return u;
}

unsigned long int degray32(unsigned long int u)
{
	u ^= (u >> 001);
	u ^= (u >> 002);
	u ^= (u >> 004);
	u ^= (u >> 010);
	u ^= (u >> 020);

	return u;
}
