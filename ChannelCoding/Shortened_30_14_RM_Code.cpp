// Implementing Shoretened (30, 14) Reed Muller Code

#include <stdint.h>
#include <stdio.h>
#include <bitset>
#include <iostream>
using namespace std;


// #include <lower_mac/tetra_rm3014.h>

/* Generator matrix from Section 8.2.3.2  */

static const uint8_t rm_30_14_gen[14][16] = {
	{ 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0 },
	{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
	{ 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1 },
	{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 }
};

static uint32_t rm_30_14_rows[14];


static uint32_t shift_bits_together(const uint8_t *bits, int len)
{
	uint32_t ret = 0;
	int i;

	for (i = len-1; i >= 0; i--)
		ret |= bits[i] << (len-1-i);

	return ret;
}



void tetra_rm3014_init(void)
{
	int i;
	uint32_t val;

	for (i = 0; i < 14; i++) {
		/* upper 14 bits identity matrix */
		val = (1 << (16+13 - i));
		/* lower 16 bits from rm_30_14_gen */
		val |= shift_bits_together(rm_30_14_gen[i], 16);
		rm_30_14_rows[i] = val;
		printf("rm_30_14_rows[%u] = 0x%08x\n", i, val);
	}
}

void tetra_rm3014_compute(const uint16_t in, uint32_t &out)
{
	int i;
	uint32_t val = 0;

	for (i = 0; i < 14; i++) {
		uint32_t bit = (in >> (14-1-i)) & 1;
		if (bit)
			val ^= rm_30_14_rows[i];
		/* we can skip the 'else' as XOR with 0 has no effect */
	}

	cout << bitset <32>(val);
	out = val;
}



