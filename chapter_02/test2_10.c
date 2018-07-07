#include <stdio.h>

char lower(char c);

int main(int argc, char const *argv[])
{
	char c = 'F';
	printf("%c\n", lower(c));
	return 0;
}

char lower(char c) {
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}