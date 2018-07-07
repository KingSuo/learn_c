#include <stdio.h>

unsigned setbits(unsigned x, char p, char n, unsigned y);

int main(int argc, char const *argv[])
{
	unsigned x = 0x0;
	unsigned y = 0x17;
	char p = 3;
	char n = 3;
	int result;
	result = setbits(x, p, n, y);
	printf("%d\n", result);
	return 0;
}

unsigned setbits(unsigned x, char p, char n, unsigned y) {
	// x = x & ~(~(~0 << n) << (p + 1 - n)) | (y & ~(~0 << n)) << (p + 1 - n);
	x = (x & (~0 << (p + 1) | ~(~0 << (p - n)))) | ((y & ~(~0 << n)) << (p - n));
	// int temp1 = 0;
	// int	temp2;
	// temp1 = ~temp1 << (p + 1);
	// temp2 = ~temp1 >> n;
	// temp1 = temp1 | temp2;
	// x = x & temp1;
	// y = y << (p + 1 - n);
	// x = y & (~temp1) | x;
	return x;
}