#include <stdio.h>

unsigned rightrot (unsigned x, int n);
int worldlength (void);

int main(int argc, char const *argv[])
{
	unsigned x = 1;	
	printf("%u\n", rightrot(x, 3));
	return 0;
}

unsigned rightrot (unsigned x, int n) {
	int worldlength(void);
	while (n--) {
		unsigned bit = (x & 1) << (worldlength() - 1);
		x >>= 1;
		x |= bit;	
	}
	return x;
}

int worldlength (void) {
	unsigned temp = (unsigned) ~0;
	int i;
	for (i = 0; (temp >>= 1) > 0; i++);
	return i;
}

