# Test commands to use with PIPEX

## What commands accept data from stdin?

- **tee** - read from standard input and write to standard output and files.
Copy standard input to each FILE, and also to standard output.

- **cat** - concatenate files and print on the standard output. With no FILE, 
or when FILE is -, read standard input.
- **cut** - ...
- **tail** - Print the last 10 lines of each FILE to standard output. 
With more than one FILE, precede each with a header giving the file name.
With no FILE, or when FILE is -, read standard input.

- **grep** - grep searches for PATTERNS in each FILE. PATTERNS is one or more
patterns separated by newline characters, and grep prints each line 
that matches a pattern. A FILE of “-” stands for standard input. If no FILE 
is given, recursive searches examine the working directory, and nonrecursive
searches read standard input.

- **sort** - sort lines of text files. Write sorted concatenation of all
FILE(s) to standard output. With no FILE, or when FILE is -, read standard
input.
- **uniq** - filter adjacent matching lines from INPUT (or standard input), 
writing to OUTPUT (or standard output).

- **tr** - Translate, squeeze, and/or delete characters from standard input, 
writing to standard output.
- **wc** - Print newline, word, and byte counts for each FILE, and a total
line if more than one FILE is specified. A word is a non-zero-length sequence 
of characters delimited by white space. With no FILE, or when FILE is -, read
standard input.

### How to use them ?

- `tee < infile` display infile to stdout
- `tr -d '\n' < infile` remove every newline from infile and display the res 
on stdout
- `wc -w < infile` counts the nb of words in infile and prints the res on stdout