#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int e, c, h, i, l, n, o, s, v;
} opt;

void parser(int argc, char *argv[], opt *options);
void main_handle(int argc, char *argv[], opt *options);
void compile_regex(regex_t *pattern_regex, int regex_flags, char *argv[],
                   int pattern_index, int argc, int e_flag);
void process_files(int argc, char *argv[], int pattern_index, int file_count,
                   regex_t *pattern_regex, opt *options,
                   int *total_num_matches);
void process_file(const char *filename, regex_t *pattern_regex, opt *options,
                  int file_count, int *total_num_matches,
                  int show_pattern_with_filename);
void append_newline(char **line_buffer);
void handle_o_flag(regex_t *pattern_regex, const char *line_buffer,
                   int file_count, const char *file_name, int line_num);
void print_and_update_results(opt *options, int file_count,
                              const char *filename, int num_matches,
                              int *total_num_matches);

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  main_handle(argc, argv, &options);

  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  int opt_char;
  const char *valid_flags = "eivclnhso";
  struct option long_options[] = {{0, 0, 0, 0}};
  while ((opt_char =
              getopt_long(argc, argv, valid_flags, long_options, NULL)) != -1) {
    switch (opt_char) {
      case 'e':
        options->e = 1;
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'o':
        options->o = 1;
        break;
      case '?':
        fprintf(stderr, "Invalid option");
        break;
    }
  }
}

void main_handle(int argc, char *argv[], opt *options) {
  int total_num_matches = 0;
  int pattern_index = optind;
  if (options->e) {
    pattern_index = pattern_index - optind;
  }
  int file_count = 0;
  if (pattern_index >= argc) {
    fprintf(stderr, "No pattern specified\n");
    exit(1);
  }
  int regex_flags = (options->i ? REG_ICASE : 0) |
                    (options->e ? REG_EXTENDED : 0) | (REG_NEWLINE);
  regex_t pattern_regex;
  compile_regex(&pattern_regex, regex_flags, argv, pattern_index, argc,
                options->e);
  for (int i = pattern_index + 1; i < argc; i++) {
    if (argv[i][0] == '-' || access(argv[i], F_OK) == -1) continue;
    file_count++;
  }
  process_files(argc, argv, pattern_index, file_count, &pattern_regex, options,
                &total_num_matches);
}

void compile_regex(regex_t *pattern_regex, int regex_flags, char *argv[],
                   int pattern_index, int argc, int e_flag) {
  int regex_status;
  if (e_flag) {
    char pattern[100] = "";
    for (int i = pattern_index; i < argc; i++) {
      if (argv[i][0] == '-') continue;
      strcat(pattern, argv[i]);
      strcat(pattern, "|");
    }
    pattern[strlen(pattern) - 1] = '\0';
    regex_status = regcomp(pattern_regex, pattern, regex_flags);
  } else {
    regex_status = regcomp(pattern_regex, argv[pattern_index], regex_flags);
  }
  if (regex_status != 0) {
    char error_buffer[100];
    regerror(regex_status, pattern_regex, error_buffer, sizeof(error_buffer));
    fprintf(stderr, "grep: %s\n", error_buffer);
  }
}

void process_files(int argc, char *argv[], int pattern_index, int file_count,
                   regex_t *pattern_regex, opt *options,
                   int *total_num_matches) {
  int show_pattern_with_filename =
      (file_count > 1) && (!options->l) &&
      (options->n || options->i || options->v || options->e) &&
      (!options->o || !options->h || file_count > 1);
  for (int i = pattern_index + 1; i < argc; i++) {
    if (argv[i][0] == '-' || access(argv[i], F_OK) == -1) continue;
    process_file(argv[i], pattern_regex, options, file_count, total_num_matches,
                 show_pattern_with_filename);
  }
  if (file_count == 0 && !options->s) {
    fprintf(stderr, "grep: no input files\n");
  }
  regfree(pattern_regex);
}

void process_file(const char *filename, regex_t *pattern_regex, opt *options,
                  int file_count, int *total_num_matches,
                  int show_pattern_with_filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (options->s) return;
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    exit(1);
  }
  int num_matches = 0, line_num = 1;
  size_t line_size = 0;
  char *line_buffer = NULL;
  while (getline(&line_buffer, &line_size, file) != -1) {
    append_newline(&line_buffer);
    int match_status = regexec(pattern_regex, line_buffer, 0, NULL, 0) == 0;
    if (options->v) match_status = !match_status;
    if (match_status) {
      num_matches++;
      if (options->l || options->c) continue;
      if (options->o) {
        handle_o_flag(pattern_regex, line_buffer, (options->h ? 0 : file_count),
                      filename, options->n ? line_num : -1);
      } else if (options->h && !options->n) {
        printf("%s", line_buffer);
      } else if (options->h && options->n) {
        printf("%d:%s", line_num, line_buffer);
      } else {
        if (show_pattern_with_filename) printf("%s:", filename);
        if (options->n) printf("%d:", line_num);
        printf("%s", line_buffer);
      }
    }
    line_num++;
  }
  free(line_buffer);
  fclose(file);
  if (options->c && options->l) {
    num_matches = 1;
  }
  print_and_update_results(options, file_count, filename, num_matches,
                           total_num_matches);
}

void append_newline(char **line_buffer) {
  size_t buffer_length = strlen(*line_buffer);
  if ((*line_buffer)[buffer_length - 1] != '\n') {
    char *new_line_buffer =
        realloc(*line_buffer, (buffer_length + 2) * sizeof(char));
    if (new_line_buffer != NULL) {
      strcat(new_line_buffer, "\n");
      *line_buffer = new_line_buffer;
    }
  }
}

void handle_o_flag(regex_t *pattern_regex, const char *line_buffer,
                   int file_count, const char *file_name, int line_num) {
  const int MAX_MATCHES = 1;
  regmatch_t matches[MAX_MATCHES];
  int pattern_count = 0;
  const char *current_line = line_buffer;
  while (regexec(pattern_regex, current_line, MAX_MATCHES, matches, 0) !=
         REG_NOMATCH) {
    if (file_count > 1 && pattern_count == 0) {
      printf("%s:", file_name);
    }
    int match_start = matches[0].rm_so;
    int match_end = matches[0].rm_eo;
    if (line_num > 0 && pattern_count == 0) {
      printf("%d:", line_num);
    }
    const int MATCH_LENGTH = match_end - match_start;
    printf("%.*s\n", MATCH_LENGTH, current_line + match_start);
    current_line += match_end;
    pattern_count++;
  }
}

void print_and_update_results(opt *options, int file_count,
                              const char *filename, int num_matches,
                              int *total_num_matches) {
  if (options->c && file_count > 1 && !options->h) {
    printf("%s:%d\n", filename, num_matches);
  }
  if ((options->c && file_count == 1) || (options->c && options->h)) {
    printf("%d\n", num_matches);
  }
  if (options->l && num_matches > 0) {
    printf("%s\n", filename);
  }
  *total_num_matches += num_matches;
}
