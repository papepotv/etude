/*
 * HELLO WORLD
 * - Cyclic Redundancy Check
 * - Greatest Common Divisor
 * - Gray Code
 * - Integer Square Root
 * written by \u5C0F\u6797\u79C0\u884C
 *
 * References:
 * - https://en.wikipedia.org/wiki/%22Hello,_World!%22_program
 */

#include <assert.h>
#include <stdio.h>
#include "crc16.h"
#include "crc32.h"
#include "gcd32.h"
#include "graycode.h"
#include "sqrt32.h"

static void test_crc16(void)
{
#if CRC16_GP == 0xA001u
	/* https://modbus.org/docs/Modbus_over_serial_line_V1_02.pdf */
	assert(crc16(0xFFFF, "\x02\x07", 2) == 0x1241);
	assert(crc16(0xFFFF, "\x02\x07\x41\x12", 4) == 0);
	/* https://reveng.sourceforge.io/crc-catalogue/16.htm#crc.cat.crc-16-usb */
	assert((crc16(0xFFFF, "123456789", 9) ^ 0xFFFF) == 0xB4C8);
	assert(crc16(0xFFFF, "123456789\xC8\xB4", 11) == 0xB001);
	assert(crc16(0, "\xFF\xFF", 2) == 0xB001);
#endif
#if CRC16_GP == 0x8408u
	/* https://reveng.sourceforge.io/crc-catalogue/16.htm#crc.cat.crc-16-ibm-sdlc */
	assert((crc16(0xFFFF, "123456789", 9) ^ 0xFFFF) == 0x906E);
	assert(crc16(0xFFFF, "123456789\x6E\x90", 11) == 0xF0B8);
	assert(crc16(0, "\xFF\xFF", 2) == 0xF0B8);
#endif
}

static void test_crc32(void)
{
#if CRC32_GP == 0xD8018001uL
	/* https://reveng.sourceforge.io/crc-catalogue/17plus.htm#crc.cat.crc-32-cd-rom-edc */
	assert(crc32(0, "123456789", 9) == 0x6EC2EDC4);
	assert(crc32(0, "123456789\xC4\xED\xC2\x6E", 13) == 0);
#endif
#if CRC32_GP == 0xEDB88320uL
	/* https://reveng.sourceforge.io/crc-catalogue/17plus.htm#crc.cat.crc-32-iso-hdlc */
	assert((crc32(0xFFFFFFFF, "123456789", 9) ^ 0xFFFFFFFF) == 0xCBF43926);
	assert(crc32(0xFFFFFFFF, "123456789\x26\x39\xF4\xCB", 13) == 0xDEBB20E3);
	assert(crc32(0, "\xFF\xFF\xFF\xFF", 4) == 0xDEBB20E3);
#endif
}

static void test_gcd32(void)
{
	assert(gcd32(0, 0) == 0);
	assert(gcd32(0, 1) == 1);
	assert(gcd32(2, 0) == 2);
	assert(gcd32(3, 3) == 3);
	assert(gcd32(8, 12) == 4);
	assert(gcd32(12, 8) == 4);
	assert(gcd32(15, 25) == 5);
	assert(gcd32(25, 15) == 5);
	assert(gcd32(30, 42) == 6);
	assert(gcd32(42, 30) == 6);
	assert(gcd32(1729, 87539319) == 7);
	assert(gcd32(87539319, 1729) == 7);
	assert(gcd32(0xFFFFFFFE, 0xFFFFFFFF) == 1);
	assert(gcd32(0xFFFFFFFF, 0xFFFFFFFE) == 1);
	assert(gcd32(0xFFFFFFFC, 0xFFFFFFFE) == 2);
	assert(gcd32(0xFFFFFFFE, 0xFFFFFFFC) == 2);
	assert(gcd32(0xFFFFFFFF, 0xFFFFFFFC) == 3);
	assert(gcd32(0xFFFFFFFC, 0xFFFFFFFF) == 3);
	assert(gcd32(0xFFFFFFFF, 0xFFFFFFFF) == 0xFFFFFFFF);
}

static int popcount_is_one(unsigned long int u)
{
	/* https://ptgmedia.pearsoncmg.com/images/9780321842688/samplepages/0321842685.pdf */
	return u != 0uL && (u & (u - 1uL)) == 0uL;
}

static int verify_graycode(unsigned long int u)
{
	return degray32(engray32(u)) == u
		&& popcount_is_one(engray32(u) ^ engray32(u - 1))
		&& popcount_is_one(engray32(u) ^ engray32(u + 1));
}

static void test_graycode(void)
{
	assert(verify_graycode(0x00000000));
	assert(verify_graycode(0x7FFFFFFF));
	assert(verify_graycode(0x80000000));
	assert(verify_graycode(0xFFFFFFFF));
	assert(verify_graycode(0x01234567));
	assert(verify_graycode(0x89ABCDEF));
	assert(verify_graycode(0xFEDCBA98));
	assert(verify_graycode(0x76543210));
}

static int verify_sqrt32(unsigned long int square)
{
	unsigned long int root = sqrt32(square);

	return (root <= 0xFFFF && root * root <= square)
		&& (0xFFFF <= root || square < (root + 1) * (root + 1));
}

static void test_sqrt32(void)
{
	assert(verify_sqrt32(0));
	assert(verify_sqrt32(1));
	assert(verify_sqrt32(2));
	assert(verify_sqrt32(3));
	assert(verify_sqrt32(4));
	assert(verify_sqrt32(5));
	assert(verify_sqrt32(6));
	assert(verify_sqrt32(7));
	assert(verify_sqrt32(8));
	assert(verify_sqrt32(9));
	assert(verify_sqrt32(10));
	assert(verify_sqrt32(42));
	assert(verify_sqrt32(1729));
	assert(verify_sqrt32(87539319));
	assert(verify_sqrt32(0xFFFFuL * 0xFFFFuL - 1));
	assert(verify_sqrt32(0xFFFFuL * 0xFFFFuL));
	assert(verify_sqrt32(0xFFFFuL * 0xFFFFuL + 1));
	assert(verify_sqrt32(0xFFFFFFFF));
}

int main(void)
{
	test_crc16();
	test_crc32();
	test_gcd32();
	test_graycode();
	test_sqrt32();
	puts("Hello, World!");
}
