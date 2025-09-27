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

#if (CRC16_GP & 0x7Fu) == 0x01u
#define XOR0(n) ((0x00u) ^ ((n) >> 0))
#define XOR1(n) (XOR0(n) ^ ((n) >> 1))
#define XOR2(n) (XOR1(n) ^ ((n) >> 2))
#define XOR3(n) (XOR2(n) ^ ((n) >> 3))
#define XOR4(n) (XOR3(n) ^ ((n) >> 4))
#define XOR5(n) (XOR4(n) ^ ((n) >> 5))
#define XOR6(n) (XOR5(n) ^ ((n) >> 6))
#define XOR7(n) (XOR6(n) ^ ((n) >> 7))
#define CRC0(n) \
	((-(XOR0(n) & 1u) & (CRC16_GP >> 7)) ^ \
	 (-(XOR1(n) & 1u) & (CRC16_GP >> 6)) ^ \
	 (-(XOR2(n) & 1u) & (CRC16_GP >> 5)) ^ \
	 (-(XOR3(n) & 1u) & (CRC16_GP >> 4)) ^ \
	 (-(XOR4(n) & 1u) & (CRC16_GP >> 3)) ^ \
	 (-(XOR5(n) & 1u) & (CRC16_GP >> 2)) ^ \
	 (-(XOR6(n) & 1u) & (CRC16_GP >> 1)) ^ \
	 (-(XOR7(n) & 1u) & (CRC16_GP >> 0)))
#else
#define XOR(a) (((a) >> 1) ^ (-((a) & 1u) & CRC16_GP))
#define CRC0(n) XOR(XOR(XOR(XOR(XOR(XOR(XOR(XOR(n))))))))
#endif

#define CRC1(n) CRC0(n), CRC0((n) + (0x01u << 0))
#define CRC2(n) CRC1(n), CRC1((n) + (0x01u << 1))
#define CRC3(n) CRC2(n), CRC2((n) + (0x01u << 2))
#define CRC4(n) CRC3(n), CRC3((n) + (0x01u << 3))
#define CRC5(n) CRC4(n), CRC4((n) + (0x01u << 4))
#define CRC6(n) CRC5(n), CRC5((n) + (0x01u << 5))
#define CRC7(n) CRC6(n), CRC6((n) + (0x01u << 6))
#define CRC8(n) CRC7(n), CRC7((n) + (0x01u << 7))

static const unsigned int table[0x100] = { CRC8(0x00u) };

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
