#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b, e, n, s, t, v, T, E;
} opt;

void parser(int argc, char *argv[], opt *options);
void reader(int argc, char *argv[], opt *options);

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  reader(argc, argv, &options);

  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  static struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {"number", 0, 0, 'n'},
                                        {0, 0, 0, 0}};
  int opt;
  int option_index = 0;
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_option,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      default:
        fprintf(stderr, "Usage:%s [-benstvTE\n", argv[0]);
        exit(1);
    }
  }
}

void reader(int argc, char *argv[], opt *options) {
  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file != NULL) {
      char gbuf;
      int changer = 0;
      int str_count = 1;
      int n_str_count = 1;
      int blank_count = 1;
      while ((gbuf = fgetc(file)) != EOF) {
        int skip = 0;
        if (gbuf != '\n') {
          blank_count = 0;
        } else if (gbuf == '\n' && !n_str_count) {
          continue;
        }
        if (options->s && blank_count > 1) {
          skip = 1;
        }
        if (options->b) {
          if (gbuf != '\n' && changer == 0) {
            changer = 1;
            printf("%6d\t", str_count);
            str_count++;
          }
        } else if (options->n && changer == 0 && skip != 1) {
          changer = 1;
          printf("%6d\t", n_str_count);
        }
        if (gbuf == '\n' && skip != 1) {
          changer = 0;
          blank_count++;
          n_str_count++;
        }
        if (options->v && (gbuf < 32) && gbuf != 9 && gbuf != 10) {
          printf("^%c", gbuf + 64);
          skip = 1;
        } else if (options->v && gbuf == 127) {
          printf("^%c", 63);
          skip = 1;
        }
        if (options->e && gbuf == '\n' && skip != 1) {
          printf("$");
        }
        if (options->t && gbuf == '\t') {
          printf("^I");
        } else if (!skip) {
          printf("%c", gbuf);
        }
      }
      fclose(file);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
    }
  }
}