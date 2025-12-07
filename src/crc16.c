/*
 * CYCLIC REDUNDANCY CHECK
 * written by \u5C0F\u6797\u79C0\u884C
 *
 * References:
 * - https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 * - https://www.nist.gov/dads/HTML/cyclicRedundancyCheck.html
 * - https://www.mathpages.com/home/kmath458.htm
 * - http://www.ross.net/crc/download/crc_v3.txt
 * - isbn-13:978-0-321-84268-8
 */

#include "crc16.h"

#if (CRC16_POLY & 0x7Fu) == 0x01u
#define XOR_0(n) (0x00u    ^ ((n) >> 0))
#define XOR_1(n) (XOR_0(n) ^ ((n) >> 1))
#define XOR_2(n) (XOR_1(n) ^ ((n) >> 2))
#define XOR_3(n) (XOR_2(n) ^ ((n) >> 3))
#define XOR_4(n) (XOR_3(n) ^ ((n) >> 4))
#define XOR_5(n) (XOR_4(n) ^ ((n) >> 5))
#define XOR_6(n) (XOR_5(n) ^ ((n) >> 6))
#define XOR_7(n) (XOR_6(n) ^ ((n) >> 7))
#define CRC(n) (0x0000u \
	^ (-(XOR_0(n) & 1u) & (CRC16_POLY >> 7)) \
	^ (-(XOR_1(n) & 1u) & (CRC16_POLY >> 6)) \
	^ (-(XOR_2(n) & 1u) & (CRC16_POLY >> 5)) \
	^ (-(XOR_3(n) & 1u) & (CRC16_POLY >> 4)) \
	^ (-(XOR_4(n) & 1u) & (CRC16_POLY >> 3)) \
	^ (-(XOR_5(n) & 1u) & (CRC16_POLY >> 2)) \
	^ (-(XOR_6(n) & 1u) & (CRC16_POLY >> 1)) \
	^ (-(XOR_7(n) & 1u) & (CRC16_POLY >> 0)))
#else
#define XOR(a) (((a) >> 1) ^ (-((a) & 1u) & CRC16_POLY))
#define CRC(n) XOR(XOR(XOR(XOR(XOR(XOR(XOR(XOR(n))))))))
#endif

#define ELEMS_0(n) CRC(n)
#define ELEMS_1(n) ELEMS_0(n), ELEMS_0((n) ^ (0x01u << 0))
#define ELEMS_2(n) ELEMS_1(n), ELEMS_1((n) ^ (0x01u << 1))
#define ELEMS_3(n) ELEMS_2(n), ELEMS_2((n) ^ (0x01u << 2))
#define ELEMS_4(n) ELEMS_3(n), ELEMS_3((n) ^ (0x01u << 3))
#define ELEMS_5(n) ELEMS_4(n), ELEMS_4((n) ^ (0x01u << 4))
#define ELEMS_6(n) ELEMS_5(n), ELEMS_5((n) ^ (0x01u << 5))
#define ELEMS_7(n) ELEMS_6(n), ELEMS_6((n) ^ (0x01u << 6))
#define ELEMS_8(n) ELEMS_7(n), ELEMS_7((n) ^ (0x01u << 7))

static const unsigned int table[0x100] = { ELEMS_8(0x00u) };

unsigned int crc16(unsigned int crc, const void *message, size_t length)
{
	if (message) {
		const unsigned char *p = message;

		while (length--) {
			crc = (crc >> 010) ^ table[(crc ^ *p++) & 0xFFu];
		}
	}

	return crc;
}
