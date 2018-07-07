#include <stdio.h>

int squeeze (char s1[], char s2[]);

int main(int argc, char const *argv[])
{
	char s1[] = "asdfgrergxvcbfxdasdfh";
	char s2[] = "asdghj";
	squeeze(s1, s2);
	printf("%s\n", s1);
	return 0;
}

int squeeze (char s1[], char s2[]) {
	int i, j, k;
	j = 0;
	for (i = k = 0; s1[i] != '\0'; i++) {
		
		while (1) {
			if (s1[i] != s2[j]) {
				++j;
				if (s2[j] == '\0') {
					j = 0;
					s1[k++] = s1[i];
					break;
				}	
			}else {
				printf("s1[%d] = s2[%d]\n", i, j);
				j = 0;
				break;
			}
		}
	}
	s1[k] = '\0';
	printf("%s\n%s\n", s1, s2);

	return 0;
}
