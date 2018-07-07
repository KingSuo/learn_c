#include <stdio.h>

unsigned invert (unsigned x, int p, int n);

int main(int argc, char const *argv[])
{
	unsigned x = 0xe;
	printf("%u\n", invert(x, 3, 3));
	return 0;
}

unsigned invert (unsigned x, int p, int n) {
	return x ^ (~((~0 << (p + 1)) | (~(~0 << (p + 1 - n)))));
}