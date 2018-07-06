#include <stdio.h>
/* counter number of lines, words and characters in the file */

#define IN 1 /* in the word*/
#define OUT 0 /* out of the word*/

int main(int argc, char const *argv[])
{
	int c, nl, nc, nw, state;
	state = OUT;
	nl = nc = nw = 0;

	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n') 
			++nl;
		if (c == ' ' || c == '\t' || c == '\n') {
			state = OUT;
		}else if (state == OUT) {		
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);

	return 0;
}