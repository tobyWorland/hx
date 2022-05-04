#include <stdio.h> // IO
#include <stdlib.h> // EXIT_SUCCESS constant and exit()
#include <string.h> // strcmp()

// How many bytes to display on the same line
#define WIDTH 0x10

void die() {
  exit(EXIT_FAILURE);
}

void usage(const char *program_name) {
  fprintf(stderr, "Usage: %s [filename]\n", program_name);
  die();
}

int main(int argc, char **argv) {
	int c;
	FILE *input = stdin;
	unsigned short col = 0;
	unsigned long offset = 0;

	if (argc > 1) {
	  if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
	    usage(argv[0]);
	  } else {
	    input = fopen(argv[1], "r");
	    if (!input) {
	      perror("open");
	      die();
	    }
	  }
	}

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

	if (fclose(input) == EOF) {
	  perror("fclose");
	  die();
	}

	putchar('\n');
	return EXIT_SUCCESS;
}
