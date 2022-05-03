#include <stdio.h>
#include <stdlib.h>

#define WIDTH 0x10

int main(int argc, char **argv) {
	int c;
	FILE *input = stdin;
	unsigned int col = 0;
	unsigned int offset = 0;

	while ((c = getc(input)) != EOF) {
		if (col == 0) {
			printf("0x%08x ", offset);
		}
		printf("%02x ", c);
		offset++;
		if (col++ == WIDTH-1) {
			putchar('\n');	
			col = 0;
		}
	}

	putchar('\n');
	return EXIT_SUCCESS;
}
