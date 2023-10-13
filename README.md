# cat_grep

# Custom Cat Utility

This is a custom implementation of the `cat` utility with additional flags.

## Table of Contents

1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Flags](#flags)
   - [-b (GNU: --number-nonblank)](#-b-gnu-number-nonblank)
   - [-e (GNU: -E, implies -v)](#-e-gnu--E-implies--v)
   - [-n (GNU: --number)](#-n-gnu--number)
   - [-s (GNU: --squeeze-blank)](#-s-gnu--squeeze-blank)
   - [-t (GNU: -T, implies -v)](#-t-gnu--T-implies--v)
4. [Installation](#installation)
5. [License](#license)

## Introduction

This custom `cat` utility is designed to provide additional functionality beyond the standard `cat` command. It includes various flags to manipulate and format the output of text files.

## Usage

To use this custom `cat` utility, you can run it from the command line, providing the desired flags and the path to the file you want to manipulate. Here's a basic usage example:

```shell
./custom-cat [OPTION] [FILE]
```

Replace `[FLAGS]` with one or more of the flags described below and `[FILE]` with the path to the file you want to process.

## Flags

### `-b (GNU: --number-nonblank)`

The `-b` flag, also known as `--number-nonblank` in GNU `cat`, numbers only non-empty lines in the output.

#### Usage

```shell
./custom-cat -b file.txt
```

#### Description

This flag will add line numbers only to lines that are not empty in the input file. It is particularly useful when you want to maintain line numbers for non-empty lines while ignoring blank lines.

### `-e (GNU: -E, implies -v)`

The `-e` flag, equivalent to `-E` in GNU `cat`, implies `-v` but also displays end-of-line characters as `$`.

#### Usage

```shell
./custom-cat -e file.txt
```

#### Description

When used with the `-e` flag, the custom `cat` utility will display end-of-line characters as `$` at the end of each line. This is useful for visually identifying the line endings.

### `-n (GNU: --number)`

The `-n` flag, also known as `--number` in GNU `cat`, numbers all output lines.

#### Usage

```shell
./custom-cat -n file.txt
```

#### Description

This flag numbers all lines in the output, including both empty and non-empty lines. It's helpful when you want to number all lines in the file.

### `-s (GNU: --squeeze-blank)`

The `-s` flag, equivalent to `--squeeze-blank` in GNU `cat`, squeezes multiple adjacent blank lines in the output.

#### Usage

```shell
./custom-cat -s file.txt
```

#### Description

When used with the `-s` flag, your custom `cat` utility will reduce multiple consecutive blank lines to a single blank line, making the output more compact.

### `-t (GNU: -T, implies -v)`

The `-t` flag, like `-T` in GNU `cat`, implies `-v but also displays tabs as `^I`.

#### Usage

```shell
./custom-cat -t file.txt
```

#### Description

When you use the `-t` flag, the custom `cat` utility will display tabs as `^I`, making it easier to visualize tab characters in the text.

## Installation

[Provide instructions for building or installing your custom `cat` utility here, if applicable.]

## License

This project is licensed under the [MIT License](LICENSE).
```

You can copy and paste this template into your `README.md` file and customize it with additional details about your custom `cat` utility, installation instructions, and any other relevant information. Be sure to replace placeholders like `[FLAGS]` and `[FILE]` with actual usage examples and details about your project.
