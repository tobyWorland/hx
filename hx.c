#include <ctype.h> // isprint()
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

void dumpFromFile(FILE *f) {
  int c;
  unsigned short col = 0;
  unsigned long offset = 0;
  char printables[WIDTH];
  printables[WIDTH] = '\0'; // Without the null terminator printf will start printing garbage from memory

  while ((c = getc(f)) != EOF) {
    // Print offset
    if (col == 0) {
      printf("0x%016x ", offset);
    }

    // Print bytes in hex
    printf("%02x ", c);
    printables[col] = isprint(c) ? c : '.';
    offset++;

    // Break line if we hit the width
    if (col++ == WIDTH-1) {
      printf(" |%s|\n", printables);
      col = 0;
    }
  }

  // Add a newline if needed
  if (col > 0)
    putchar('\n');
}

int main(int argc, char **argv) {
  FILE *input = stdin;

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

  dumpFromFile(input);

  if (fclose(input) == EOF) {
    perror("fclose");
    die();
  }

  return EXIT_SUCCESS;
}
