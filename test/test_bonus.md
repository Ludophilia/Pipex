# Test battery for pipex bonus

## Program description

Pipex is a program that simulates the shell script command below:

``` < file1 cmd1 [args] | cmd2 [args] > file2 ```

Where `file1` and `file2` are files and `cmd1` and `cmd2` are executables.

## Usage

```./pipex file1 cmd1 cmd2 file2```
```./pipex file1 "cmd1 args" "cmd2 args" file2```

## Bonus

The bonus part is roughly similar to the mandatory part except in the fact that
it should simulate the shell script command below:

- `<< here_doc cmd1 [args] | cmd2 [args] >> file2`
	- input to `cmd1` is managed via `here documents` instead of `file1`
	- the output of `cmd2` is appended to the already existing content, if it
	 exists of course, instead of just erasing it...

## Test suite


HOLDUP HOLDUP HOLDUP

valgrind ./pipex HERE_DOC cat tee outfile
> pipex: HERE_DOC: No such file or directory

BUT THERE IS SOME ERRORS. CORRECT THIS ASAP.





## HERE DOC level

### A basic example

- [x] `<< EOF cat | strings | nl >> test/outfile`
	  `./pipex here_doc EOF cat strings nl test/outfile`
	- [x] User input: `123\n1234\n123\nEOF`
	- [x] Displays the input line by line if nb of chars >= 4 with the line 
	number before
	- [x] Do it twice to check if file appending works
	- [x] Leak protected?
	- [x] No tmp file left after use

### A nastier example (stops at LIMITER, nothing else)

- [x] `<< EOF cat | strings | nl >> test/outfile`
	  `./pipex here_doc EOF cat strings nl test/outfile`
	- [x] User input: `123\n1234\n123\nEOF?\neof\nEOF  \nEOF.\nEOF`
	- [x] Displays the input line by line if nb of chars >= 4 with the line 
	number before
	- [x] Do it twice to check if file appending works
	- [x] Leak protected?
	- [x] No tmp file left after use

### Is the file created if does not exist

- [x] `<< EOF cat | strings | nl >> test/outfile2`
	`./pipex here_doc EOF cat strings nl test/outfile2`
	- [x] User input: `123\n1234\n123\nEOF`
	- [x] Displays the input line by line if nb of chars >= 4 with the line 
	number before
	- [x] File created?
	- [x] Do it twice to check if file appending works
	- [x] No tmp file left after use

## ./pipex level

### Not enough args for here_docs (argc < 6)

- [x] `./pipex here_doc strings nl test/outfile`
	  - [x] Error message is returned
	  - [x] Leak protected?
	  - [x] No tmp file left after use

### Args swapped with here_docs (1)

- [x] `./pipex here_doc test/outfile strings tee nl`
	`<< test/outfile strings | tee >> nl`
	- [x] This is not an error, test/outfile is just the limiter and nl the 
	output file file
	- [x] User input: `WOWOW\ntest/outfile`
	- [x] Leak protected?
	- [x] No tmp file left after use?

### Permission errors with Args swapped with here_docs (2)

- [x] `./pipex here_doc strings tee test/outfile nl`
	   `<< strings tee | test/outfile >> nl`
	- [x] Takes the user input and returns an error, test/outfile
	permission denied as test/outfile is not executable
	- [x] User input: `WOWOW\ntest/outfile\ntee\nstrings`
	- [x] Leak protected?
	- [x] No tmp file left after use?
	- [x] nl still created despite the error?
