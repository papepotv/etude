/*
 * CYCLIC REDUNDANCY CHECK
 * written by \u5C0F\u6797\u79C0\u884C
 */

#ifndef PAPEPOTV_CRC32_H
#define PAPEPOTV_CRC32_H

#include <stddef.h>

#if 0
#define CRC32_POLY 0xD8018001uL /* x^0 + x^1 + x^3 + x^4 + x^15 + x^16 + x^31 + x^32 */
#else
#define CRC32_POLY 0xEDB88320uL /* x^0 + x^1 + x^2 + x^4 + x^5 + x^7 + x^8 + x^10 + x^11 + x^12 + x^16 + x^22 + x^23 + x^26 + x^32 */
#endif

unsigned long int crc32(unsigned long int crc, const void *message, size_t length);

#endif
