#include <stdio.h>

int htoi (char s[]);

int main(int argc, char const *argv[])
{
	
	return 0;
}

int htoi (char s[]) {
	int i, value;
	value = 0;

	for (i = 2; s[i] != '\0'; ++i)
		value = value * 16 + s[i];

	return value;
}