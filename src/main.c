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
	assert(crc16(0u, NULL, 0) == 0u);
	assert(crc16(42u, NULL, 0) == 42u);
	assert(crc16(42u, NULL, 9) == 42u);
	assert(crc16(42u, "123456789", 0) == 42u);
#if CRC16_POLY == 0xA001u
	/* https://modbus.org/docs/Modbus_over_serial_line_V1_02.pdf */
	assert(crc16(0xFFFFu, "\x02\x07", 2) == 0x1241u);
	assert(crc16(0xFFFFu, "\x02\x07\x41\x12", 4) == 0u);
	/* https://reveng.sourceforge.io/crc-catalogue/16.htm#crc.cat.crc-16-usb */
	assert((crc16(0xFFFFu, "123456789", 9) ^ 0xFFFFu) == 0xB4C8u);
	assert(crc16(0xFFFFu, "123456789\xC8\xB4", 11) == 0xB001u);
	assert(crc16(0u, "\xFF\xFF", 2) == 0xB001u);
#endif
#if CRC16_POLY == 0x8408u
	/* https://reveng.sourceforge.io/crc-catalogue/16.htm#crc.cat.crc-16-ibm-sdlc */
	assert((crc16(0xFFFFu, "123456789", 9) ^ 0xFFFFu) == 0x906Eu);
	assert(crc16(0xFFFFu, "123456789\x6E\x90", 11) == 0xF0B8u);
	assert(crc16(0u, "\xFF\xFF", 2) == 0xF0B8u);
#endif
}

static void test_crc32(void)
{
	assert(crc32(0uL, NULL, 0) == 0uL);
	assert(crc32(42uL, NULL, 0) == 42uL);
	assert(crc32(42uL, NULL, 9) == 42uL);
	assert(crc32(42uL, "123456789", 0) == 42uL);
#if CRC32_POLY == 0xD8018001uL
	/* https://reveng.sourceforge.io/crc-catalogue/17plus.htm#crc.cat.crc-32-cd-rom-edc */
	assert(crc32(0uL, "123456789", 9) == 0x6EC2EDC4uL);
	assert(crc32(0uL, "123456789\xC4\xED\xC2\x6E", 13) == 0uL);
#endif
#if CRC32_POLY == 0xEDB88320uL
	/* https://reveng.sourceforge.io/crc-catalogue/17plus.htm#crc.cat.crc-32-iso-hdlc */
	assert((crc32(0xFFFFFFFFuL, "123456789", 9) ^ 0xFFFFFFFFuL) == 0xCBF43926uL);
	assert(crc32(0xFFFFFFFFuL, "123456789\x26\x39\xF4\xCB", 13) == 0xDEBB20E3uL);
	assert(crc32(0uL, "\xFF\xFF\xFF\xFF", 4) == 0xDEBB20E3uL);
#endif
}

static void test_gcd32(void)
{
	assert(gcd32(0uL, 0uL) == 0uL);
	assert(gcd32(0uL, 1uL) == 1uL);
	assert(gcd32(2uL, 0uL) == 2uL);
	assert(gcd32(3uL, 3uL) == 3uL);
	assert(gcd32(8uL, 12uL) == 4uL);
	assert(gcd32(12uL, 8uL) == 4uL);
	assert(gcd32(15uL, 25uL) == 5uL);
	assert(gcd32(25uL, 15uL) == 5uL);
	assert(gcd32(30uL, 42uL) == 6uL);
	assert(gcd32(42uL, 30uL) == 6uL);
	assert(gcd32(1729uL, 87539319uL) == 7uL);
	assert(gcd32(87539319uL, 1729uL) == 7uL);
	assert(gcd32(0xFFFFFFFEuL, 0xFFFFFFFFuL) == 1uL);
	assert(gcd32(0xFFFFFFFFuL, 0xFFFFFFFEuL) == 1uL);
	assert(gcd32(0xFFFFFFFCuL, 0xFFFFFFFEuL) == 2uL);
	assert(gcd32(0xFFFFFFFEuL, 0xFFFFFFFCuL) == 2uL);
	assert(gcd32(0xFFFFFFFFuL, 0xFFFFFFFCuL) == 3uL);
	assert(gcd32(0xFFFFFFFCuL, 0xFFFFFFFFuL) == 3uL);
	assert(gcd32(0xFFFFFFFFuL, 0xFFFFFFFFuL) == 0xFFFFFFFFuL);
}

static int popcount_is_one(unsigned long int u)
{
	/* https://ptgmedia.pearsoncmg.com/images/9780321842688/samplepages/0321842685.pdf */
	return u != 0uL && (u & (u - 1uL)) == 0uL;
}

static int verify_graycode(unsigned long int u)
{
	return degray32(engray32(u)) == u
		&& popcount_is_one(engray32(u) ^ engray32(u - 1uL))
		&& popcount_is_one(engray32(u) ^ engray32(u + 1uL));
}

static void test_graycode(void)
{
	assert(verify_graycode(0x00000000uL));
	assert(verify_graycode(0x7FFFFFFFuL));
	assert(verify_graycode(0x80000000uL));
	assert(verify_graycode(0xFFFFFFFFuL));
	assert(verify_graycode(0x01234567uL));
	assert(verify_graycode(0x89ABCDEFuL));
	assert(verify_graycode(0xFEDCBA98uL));
	assert(verify_graycode(0x76543210uL));
}

static int verify_sqrt32(unsigned long int square)
{
	unsigned long int root = sqrt32(square);

	return (root <= 0xFFFFuL && root * root <= square)
		&& (0xFFFFuL <= root || square < (root + 1uL) * (root + 1uL));
}

static void test_sqrt32(void)
{
	assert(verify_sqrt32(0uL));
	assert(verify_sqrt32(1uL));
	assert(verify_sqrt32(2uL));
	assert(verify_sqrt32(3uL));
	assert(verify_sqrt32(4uL));
	assert(verify_sqrt32(5uL));
	assert(verify_sqrt32(6uL));
	assert(verify_sqrt32(7uL));
	assert(verify_sqrt32(8uL));
	assert(verify_sqrt32(9uL));
	assert(verify_sqrt32(10uL));
	assert(verify_sqrt32(42uL));
	assert(verify_sqrt32(1729uL));
	assert(verify_sqrt32(87539319uL));
	assert(verify_sqrt32(0xFFFFuL * 0xFFFFuL - 1uL));
	assert(verify_sqrt32(0xFFFFuL * 0xFFFFuL));
	assert(verify_sqrt32(0xFFFFuL * 0xFFFFuL + 1uL));
	assert(verify_sqrt32(0xFFFFFFFFuL));
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
