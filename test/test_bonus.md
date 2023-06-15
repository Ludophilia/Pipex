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

## About multiple pipes

### Example

- [x] `< /dev/random tr -cd '[:print:]' | fold -w 30 | head -15 | nl > /dev/stdout`
	- `./pipex /dev/random "tr -cd '[:print:]'" "fold -w 30" "head -15" nl /dev/stdout`
	- `valgrind ./pipex /dev/random "tr -cd '[:print:]'" "fold -w 30" "head -15" nl /dev/stdout`
	- [x] prints 15 lines of 30 random characters preceded by the line number
	- [x] `$SHELL` displays the prompt
	- [x] Leak protected?

### Parallelism tests

- [x] `time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout)`
	`time ./pipex /dev/stdin "sleep 5" "sleep 5" "sleep 5" /dev/stdout`
	- [x] execute simultaneously all `sleep` processes for about 5 seconds,
	see time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout).
	- [x] no process is blocked as `sleep` does not read `stdin` nor 
	writes `stdout`
	- [x] `$SHELL` displays the prompt

### Independent commands tests

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | yes 42 > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" "yes 42" /dev/stdout`
	`valgrind ./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" "yes 42" /dev/stdout`
	- [x] writes indefinitely `42` on `/dev/stdout`
	- [x] `$SHELL` does not display the prompt
	- [x] Leak protected?

### Dependent nonblocking commands tests

- [x] `< test/infile strings | nl | tee > /dev/stdout`
	`./pipex test/infile strings nl tee /dev/stdout`
	`valgrind ./pipex test/infile strings nl tee /dev/stdout`
	- [x] prints the 2 lines that have 4 or more charaters
	- [x] `$SHELL` displays the prompt (`strings` has NOTHING ELSE to READ)
	- [x] Leak protected?

- [x] `< /dev/urandom strings | nl | tee > /dev/stdout`
	`./pipex /dev/urandom strings nl tee /dev/stdout`
	`valgrind ./pipex /dev/urandom strings nl tee /dev/stdout`
	- [x] prints and count INDEFINITELY printable character sequences from 
	/dev/random that are at least 4 bytes long
	- [x] `$SHELL` does not give back the prompt (`strings` has always something
	to read)
	- [x] Leak protected?

### Mixed dependence commands tests

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | head > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" head /dev/stdout`
	`valgrind ./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" head /dev/stdout`
	- [x] displays 10 `YESYESYES` on stdout
	- [x] `$SHELL` displays the prompt
	- [x] Leak protected?

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | strings | tee | head > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" strings tee head /dev/stdout`
	`valgrind ./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" strings tee head /dev/stdout`
	- [x] displays 10 `YESYESYES` on stdout
	- [x] `$SHELL` displays the prompt
	- [x] Leak protected?

## About HERE DOCS

### A basic example

- [ ] `<< EOF cat | strings | nl >> test/outfile`
	  `./pipex here_doc EOF cat strings nl test/outfile`
	  `valgrind ./pipex here_doc EOF cat strings nl test/outfile`
	- [x] User input: `123\n1234\n123\nEOF`
	- [x] Displays the input line by line if nb of chars >= 4 with the line 
	number before
	- [x] Do it twice to check if file appending works
	- [x] Leak protected?
	- [x] No tmp file left after use

### A nastier example (stops at LIMITER, nothing else)

- [x] `<< EOF cat | strings | nl >> test/outfile`
	  `./pipex here_doc EOF cat strings nl test/outfile`
	  `valgrind ./pipex here_doc EOF cat strings nl test/outfile`
	- [x] User input: `123\n1234\n123\nEOF?\neof\nEOF  \nEOF.\nEOF`
	- [x] Displays the input line by line if nb of chars >= 4 with the line 
	number before
	- [x] Do it twice to check if file appending works
	- [x] Leak protected?
	- [x] No tmp file left after use

### Is the file created if does not exist

- [ ] `<< EOF cat | strings | nl >> test/outfile2`
	`./pipex here_doc EOF cat strings nl test/outfile2`
	`valgrind ./pipex here_doc EOF cat strings nl test/outfile2`
	- [x] User input: `123\n1234\n123\nEOF`
	- [x] Displays the input line by line if nb of chars >= 4 with the line 
	number before
	- [x] File created?
	- [x] Leak protected?
	- [x] Do it twice to check if file appending works
	- [x] No tmp file left after use

### The program is interrupted (SIGINT) while getting the heredoc...
	- [ ] Getting too far (can't even handle signals in this project)

## ./pipex level

### Not enough args for here_docs (argc < 6)

- [ ] `./pipex here_doc strings nl test/outfile`
	`valgrind ./pipex here_doc strings nl test/outfile`
	  - [x] Error message is returned
	  - [x] Leak protected?
	  - [x] No tmp file left after use

### Args swapped with here_docs (1)

- [ ] `./pipex here_doc test/outfile strings tee nl`
	`valgrind ./pipex here_doc test/outfile strings tee nl`
	`<< test/outfile strings | tee >> nl`
	- [x] This is not an error, test/outfile is just the limiter and nl the 
	output file
	- [x] User input: `WOWOW\ntest/outfile`
	- [x] nl file created?
	- [x] Leak protected?
	- [x] No tmp file left after use?

### Permission errors with Args swapped with here_docs (2)

- [x] `./pipex here_doc strings tee test/outfile nl`
	`valgrind ./pipex here_doc strings tee test/outfile nl`
	   `<< strings tee | test/outfile >> nl`
	- [x] Takes the user input and returns an error, test/outfile
	permission denied as test/outfile is not executable
	- [x] User input: `WOWOW\ntest/outfile\ntee\nstrings`
	- [x] Leak protected?
	- [x] No tmp file left aftestter use?
	- [x] nl still created despite the error?

## < file1 level

### infile (argv[1]) does not exist:
- [x] `< /dev/gf tee | cat | fold -w 1 > /dev/stdout`
	`./pipex /dev/gf tee cat "fold -w 1" /dev/stdout`
	- `valgrind ./pipex /dev/gf tee cat "fold -w 1" /dev/stdout`
	- [x] Expected error message
		- `bash: <filename>: No such file or directory`
		- `pipex: <filename>: No such file or directory`
	- [x] Leak protected?

### infile (argv[1]) exists but its folder is not searchable (no x permission)
- [x] `< test/infile tee | cat | tac > /dev/stdout`
	- `./pipex test/infile tee cat tac /dev/stdout`
	- `valgrind ./pipex test/infile tee cat tac /dev/stdout`
	- [x] Change file permissions on test/
	- [x] Expected error message
		- `bash: <folder>/<filename>: Permission denied`
		- `pipex: <folder>/<filename>: Permission denied`
	- [x] Leak protected?

### infile (argv[1]) is not readable (no r permission):
- [x] `< test/infile tee | cat | tac > /dev/stdout`
	- `./pipex test/infile tee cat tac /dev/stdout`
	- `valgrind ./pipex test/infile tee cat tac /dev/stdout`
	- [x] Change file permissions on test/infile
	- [x] Expected error message
		- `bash: <filename>: Permission denied`
		- `pipex: <filename>: Permission denied`
	- [x] Leak protected?

### infile (argv[1]) is a directory:
- [x] `< . tee | head -3 nl > /dev/stdout`
	- `./pipex . tee "head -3" nl /dev/stdout`
	- `valgrind ./pipex . tee "head -3" nl /dev/stdout`
	- [x] Expected error message
		- `<command>: read error: Is a directory` (depend on the command)
		- (difference in the command path because of execve)
	- [x] Leak protected?

### cmd1 | cmd2 level

#### cdm1 (argv[2]) or cmd2 (argv[3]) is NOT executable:
- [x] `< /dev/random test/fcmd | nl > /dev/stdout`
	- `./pipex /dev/random test/fcmd nl /dev/stdout`
	- `< /dev/random tee | test/fcmd > /dev/stdout`
	- `./pipex /dev/random tee test/fcmd /dev/stdout`
	- [x] `valgrind ./pipex /dev/random test/fcmd nl /dev/stdout`
	- [x] `valgrind ./pipex /dev/random tee test/fcmd nl /dev/stdout`
	- [x] Create a command fcmd
	- [x] Expected error message
		- `bash: <cmd>: No such file or directory` or `bash: <cmd>: Permission
		denied`
		- `pipex: <cmd>: No such file or directory` or `pipex: <cmd>: Permission
		denied`
	- [x] Leak protected?

#### cdm1 (argv[2]) or cmd2 (argv[3]) does not exist (not found in $PATH):
	
- [x] `< /dev/random abc | def | xyz > /dev/stdout`
	- [x] `valgrind ./pipex /dev/random abc def xyz /dev/stdout`
	- [x] Expected error message
		- `bash: <cmd>: command not found`
		- `pipex: <cmd>: command not found`
	- [x] Leak protected?

#### $PATH is missing:
- [x] `env -u PATH < /dev/random tee | head -c 80 | nl > /dev/stdout`
	- `env -u PATH ./pipex /dev/random tee "head -c 80" nl /dev/stdout`
	- `/usr/bin/valgrind ./pipex /dev/random tee "head -c 80" nl /dev/stdout`
	- [x] Expected error message
		- [No error message expected]
	- [x] Leak protected?
		- [Test it in a subshell with no PATH]

### > file2 level
	
#### outfile (argv[4]) does not exist:
- [x] `< /dev/random strings | head | nl > test/outfile`
	- `./pipex /dev/random strings head nl test/outfile`
	- `valgrind ./pipex /dev/random strings head nl test/outfile`
		- [x] `outfile` is CREATED and then written on
		- [x] Leak protected?

#### outfile (argv[4]) does not exist and the parent folder is not searchable:
- [x] `< /dev/random strings | head | nl > test/outfile2`
	- `./pipex /dev/random strings head nl test/outfile2`
	- `valgrind ./pipex /dev/random strings head nl test/outfile2`
	- [x] Change perms on test/
	- [x] Expected error message
		- `bash: <filename>: Permission denied`
		- `pipex: <filename>: Permission denied`
	- [x] Leak protected?

#### outfile (argv[4]) exists but is not writable:
- [x] `< /dev/random strings | head | nl | nl | fold -w 30 > test/foutfile`
	- `./pipex /dev/random strings head nl nl "fold -w 30" test/foutfile`
	- `valgrind ./pipex /dev/random strings head nl nl "fold -w 30" test/foutfile`
	- [x] Create test/foutfile and remove w perm
	- [x] Expected error message
		- `bash: <filename>: Permission denied`
		- `pipex: <filename>: Permission denied`
	- [x] Leak protected?

#### outfile (argv[4]) is a directory:
- [x] `< /dev/random tr -cd '[:print:]' | fold -w 30 | head -15 | nl > .`
- [x] `./pipex /dev/random "tr -cd '[:print:]" "fold -w 30" "head -15" nl .`
- [x] `valgrind ./pipex /dev/random "tr -cd '[:print:]" "fold -w 30" "head -15" nl .`
	- [x] Expected error message
		- `bash: <directory>: is a directory`
		- `pipex: <directory>: is a directory`
	- [x] Leak protected?
