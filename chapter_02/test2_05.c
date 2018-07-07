#include <stdio.h>

int any(char s1[], char s2[]);
int any2(char s1[], char s2[]);

int main(int argc, char const *argv[])
{
	char s1[] = "asdfghjkl";
	char s2[] = "lkjksdbfkkjnask";
	printf("%d\n", any(s1, s2));
	printf("%d\n", any2(s1, s2));

	return 0;
}

int any(char s1[], char s2[]) {
	
	for (int i = 0; s2[i] != '\0'; ++i) {
		for (int j = 0; s1[j] != '\0'; ++j) {
			if (s2[i] == s1[j]) {
				return j;
			}
		}
		return -1;
	}
}

int any2(char s1[], char s2[]) {
	
	for (int i = 0; s1[i] != '\0'; ++i) {
		for (int j = 0; s2[j] != '\0'; ++j) {
			if (s2[i] == s1[j]) {
				return i;
			}
		}
		return -1;
	}
}
