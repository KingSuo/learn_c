#include <stdio.h>

int htoi (char s[]);

int main(int argc, char const *argv[])
{
	printf("%d\n", htoi("0xFF"));
	return 0;
}

int htoi (char s[]) {
	int i, value, temp;
	value = 0;

	for (i = 2; (temp = s[i]) != '\0'; ++i) {
		if (temp >= '0' && temp <= '9')
			temp = (int) temp - 48;		//temp = temp - '0'
		if (temp >= 'a' && temp <= 'f')
			temp = (int) temp - 87;		//temp = temp - 'a' + 10
		if (temp >= 'A' && temp <= 'F')
			temp = (int) temp - 55;		//temp = temp - 'A' + 10
		value = value * 16 + temp;
	}

	return value;
}