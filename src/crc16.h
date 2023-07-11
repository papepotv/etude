/*
 * CYCLIC REDUNDANCY CHECK
 * written by \u5C0F\u6797\u79C0\u884C
 */

#ifndef PAPEPOTV_CRC16_H
#define PAPEPOTV_CRC16_H

#include <stddef.h>

#if 1
#define CRC16_GP 0xA001u /* x^0 + x^2 + x^15 + x^16 */
#else
#define CRC16_GP 0x8408u /* x^0 + x^5 + x^12 + x^16 */
#endif

unsigned int crc16(unsigned int crc, const void *message, size_t length);

#endif
