# Custom Grep Utility

This is a custom implementation of the `grep` utility with additional flags.

## Table of Contents

1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Flags](#flags)
   - [-e pattern](#-e-pattern)
   - [-i (Ignore uppercase vs. lowercase)](#-i-ignore-uppercase-vs-lowercase)
   - [-v (Invert match)](#-v-invert-match)
   - [-c (Output count of matching lines only)](#-c-output-count-of-matching-lines-only)
   - [-l (Output matching files only)](#-l-output-matching-files-only)
   - [-n (Precede each matching line with a line number)](#-n-precede-each-matching-line-with-a-line-number)
   - [-h (Output matching lines without preceding them by file names)](#-h-output-matching-lines-without-preceding-them-by-file-names)
   - [-s (Suppress error messages about nonexistent or unreadable files)](#-s-suppress-error-messages-about-nonexistent-or-unreadable-files)
   - [-f file (Take regexes from a file)](#-f-file-take-regexes-from-a-file)
   - [-o (Output the matched parts of a matching line)](#-o-output-the-matched-parts-of-a-matching-line)

## Introduction

This custom `grep` utility is designed to provide advanced text searching functionality with additional flags for more precise search results.

## Usage

To use this custom `grep` utility, you can run it from the command line, providing the desired flags and the pattern you want to search for. Here's a basic usage example:

```shell
./custom-grep [FLAGS] pattern [FILE]
```

Replace `[FLAGS]` with one or more of the flags described below, `pattern` with the search pattern, and `[FILE]` with the path to the file(s) you want to search within.

## Flags

### `-e pattern`

The `-e` flag allows you to specify the search pattern. It is often used when the pattern begins with a hyphen `-`.

#### Usage

```shell
./custom-grep -e pattern file.txt
```

#### Description

Use this flag to specify the search pattern that may start with a hyphen (`-`). This ensures the search pattern is not treated as an option.

### `-i (Ignore uppercase vs. lowercase)`

The `-i` flag, when enabled, makes the search case-insensitive.

#### Usage

```shell
./custom-grep -i pattern file.txt
```

#### Description

Enabling this flag allows your custom `grep` utility to ignore the distinction between uppercase and lowercase letters during the search. It makes the search case-insensitive.

### `-v (Invert match)`

The `-v` flag inverts the match, showing lines that do not contain the specified pattern.

#### Usage

```shell
./custom-grep -v pattern file.txt
```

#### Description

When used with the `-v` flag, your custom `grep` utility will display lines that do not contain the specified search pattern, effectively inverting the match.

### `-c (Output count of matching lines only)`

The `-c` flag counts and outputs the number of lines that match the pattern.

#### Usage

```shell
./custom-grep -c pattern file.txt
```

#### Description

With the `-c` flag, your custom `grep` utility will count and display the number of lines that match the specified pattern.

### `-l (Output matching files only)`

The `-l` flag outputs the names of files that contain the search pattern.

#### Usage

```shell
./custom-grep -l pattern file1.txt file2.txt
```

#### Description

When used with the `-l` flag, your custom `grep` utility will display the names of files that contain the specified search pattern.

### `-n (Precede each matching line with a line number)`

The `-n` flag precedes each matching line with a line number.

#### Usage

```shell
./custom-grep -n pattern file.txt
```

#### Description

By using the `-n` flag, your custom `grep` utility will add line numbers to the output, making it easier to identify the line numbers of matching lines.

### `-h (Output matching lines without preceding them by file names)`

The `-h` flag suppresses the display of file names when outputting matching lines.

#### Usage

```shell
./custom-grep -h pattern file.txt
```

#### Description

When the `-h` flag is enabled, your custom `grep` utility will only display the matching lines without prepending them with file names.

### `-s (Suppress error messages about nonexistent or unreadable files)`

The `-s` flag suppresses error messages related to files that are nonexistent or unreadable.

#### Usage

```shell
./custom-grep -s pattern non_existent_file.txt
```

#### Description

Enabling the `-s` flag will prevent your custom `grep` utility from displaying error messages for files that do not exist or cannot be read.

### `-f file (Take regexes from a file)`

The `-f` flag allows you to read search patterns from a file.

#### Usage

```shell
./custom-grep -f patterns.txt file.txt
```

#### Description

When you use the `-f` flag, your custom `grep` utility will read search patterns from the specified file, making it convenient for batch searching.

### `-o (Output the matched parts of a matching line)`

The `-o` flag outputs only the matched parts of a matching line.

#### Usage

```shell
./custom-grep -o pattern file.txt
```

#### Description

When the `-o` flag is enabled, your custom `grep` utility will display only the parts of each line that match the search pattern, excluding the rest of the line.

## Installation

[In the progress...]

## License

This project is licensed under the [MIT License](LICENSE).
```

You can copy and paste this template into your `README.md` file and customize it with additional details about your custom `grep` utility, installation instructions, and any other relevant information. Be sure to replace placeholders like `[FLAGS]`, `pattern`, and `[FILE]` with actual usage examples and details about your project.
