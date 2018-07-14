#include <stdio.h>

int main(int argc, char const *argv[])
{
	char *ptr = "geeksforgeeks";
	printf("%c\n", *&*&*ptr);	//g
	printf("%s\n", &*&*ptr);	//geeksforgeeks
	printf("%s\n", &*ptr);	//geeksforgeeks
	printf("%s\n", ptr);	//geeksforgeeks
	printf("%p\n", ptr);	//0x558d3eb0f8a4
	printf("%c\n", *ptr);	//g
	printf("%s\n", *&ptr);	//geeksforgeeks
	printf("%p\n", *&ptr);	//0x558d3eb0f8a4
	getchar();
	return 0;
}