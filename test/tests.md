# Test battery for pipex

## Program description

Pipex is a program that simulates the shell script command below:

``` < file1 cmd1 [args] | cmd2 [args] > file2 ```

Where `file1` and `file2` are files and `cmd1` and `cmd2` are executables.

## Usage

```./pipex file1 cmd1 cmd2 file2```
```./pipex file1 "cmd1 args" "cmd2 args" file2```

## Examples

``` ./pipex /dev/null tee cat /dev/stdout ```
``` ./pipex infile tee "wc -w" /dev/stdout ```

## What commands prints data

- **yes**
- **echo**
- **pritnf**

## What commands accept data from stdin?

- **tee** - read from standard input and write to standard output and files.
Copy standard input to each FILE, and also to standard output.
- **cat** - concatenate files and print on the standard output. With no FILE, 
or when FILE is -, read standard input.

- **tail** - Print the last 10 lines of each FILE to standard output. 
With more than one FILE, precede each with a header giving the file name.
With no FILE, or when FILE is -, read standard input.
- **head** - 

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
- **cut** - ...

- **strings**
- **fold**

- **wc** - Print newline, word, and byte counts for each FILE, and a total
line if more than one FILE is specified. A word is a non-zero-length sequence 
of characters delimited by white space. With no FILE, or when FILE is -, read
standard input.
- **nl** -

## Test suite 

### Parallelism tests

- [x] `time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout)`
	`time ./pipex /dev/stdin "sleep 5" "sleep 5" "sleep 5" /dev/stdout`
	- execute simultaneously all `sleep` processes for about 5 seconds,
	see time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout).
	- no process is blocked as `sleep` does not read `stdin` nor 
	writes `stdout`.
	- `$SHELL` displays the prompt

- [x] `time (< /dev/zero sleep 5 | sleep 10 > /dev/null)`
	`time ./pipex /dev/zero "sleep 5" "sleep 10" /dev/null`
	- last 10 seconds, use time to check
	- `$SHELL` displays the prompt

- [x] `time (< /dev/zero sleepina 5 | sleep 10 > /dev/null)`
	`time ./pipex /dev/zero "sleepina 5" "sleep 10" /dev/null`

### Independent commands tests

- [x] `< /dev/stdin cat | ls /dev/stdout > /dev/stdout`
	`./pipex /dev/stdin cat "ls /dev/stdout" /dev/stdout`
	- directly list via `ls` the `/dev/stdout` file AS `ls` does not depend on 
	its `stdin` (here the pipe read end) to start processing.
	- wait for the user's input via `/dev/stdout` to start processing `cat`
	- `cat` displays nothing as the result is sent to the write end of the pipe.
	- `$SHELL` displays the prompt (which is not the case with 
	`< /dev/stdin cat` where `cat` just expects more...)

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" /dev/stdout`
	- writes indefinitely `YESYESYES` on `/dev/stdout`
	- `$SHELL` does not give back the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [ ] `< /dev/random yes YAAAAAAAS | yess YESYESYES > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yess YESYESYES" /dev/stdout`
	- returns `bash: yess: command not found` nothing more.
	- [x] The leaks are not correctly managed on the one of the childs
	- [ ] the error propagates (multiple error messages), which is not good
	either... 

- [ ] `< /dev/random yass YAAAAAAAS | yess YESYESYES > /dev/stdout`
	`./pipex /dev/random "yass YAAAAAAAS" "yess YESYESYES" /dev/stdout`
	- returns `bash: yess: command not found` nothing more.
	- [x] The leaks are not correctly managed on the one of the childs
	- [ ] the error propagates (multiple error messages), which is not good
	either... 
	- [ ] the error messages are intertwinded....

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | yes 42 > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" "yes 42" /dev/stdout`
	- writes indefinitely `42` on `/dev/stdout`
	- `$SHELL` does not display the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

### Dependent blocking commands tests

- [x] `< /dev/random cat | head -c 80 > /dev/stdout`
	`./pipex /dev/random cat "head -c 80" /dev/stdout`
	- displays the first 80 bytes from random.
	- `$SHELL` displays the prompt

- [x] `< /dev/stdin cat | head -c 1 > /dev/stdout`
	`./pipex /dev/stdin cat "head -c 1" /dev/stdout`
	- display 1 byte sent by the user, as `head` will close the pipe afterwards.
	- `$SHELL` displays the prompt after 1 more try.

- [x] `< /dev/random yes | head > /dev/stdout`
	`./pipex /dev/random yes head /dev/stdout`
	- displays 10 `y`
	- `$SHELL` displays the prompt

### Dependent nonblocking commands tests

- [x] `< /dev/stdin cat | tee /dev/null > /dev/stdout`
	`./pipex /dev/stdin cat "tee /dev/null" /dev/stdout`
	- wait for the user's input via `/dev/stdout` to start processing `cat`
	- `cat` reads `/dev/stdin` and displays nothing on `stdout` as the result
	is sent to the write end of the pipe.
	- `tee` reads `stdin` (the read end of the pipe) so the process will be 
	blocked until `cat` sends anything...
	- `$SHELL` does not give back the prompt (send `EOF` via `ctrl+d`)
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [x] `< /dev/urandom strings | nl > /dev/stdout`
	`./pipex /dev/urandom strings nl /dev/stdout`
	- prints and count INDEFINITELY printable character sequences from 
	/dev/urandom that are at least 4 bytes long
	- `$SHELL` does not give back the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [x] `< /dev/null yes LOSER | nl > /dev/stdout`
	`./pipex /dev/null "yes LOSER" nl /dev/stdout`
	- prints `LOSER` indefinitely with the line number
	- `$SHELL` does not give back the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [x] `< test/infile strings | nl | tee > /dev/stdout`
	`./pipex test/infile strings nl tee /dev/stdout`
	- prints the 2 lines that have 4 or more charaters
	- `$SHELL` displays the prompt (`strings` has NOTHING ELSE to READ)

- [x] `< /dev/urandom strings | nl | tee > /dev/stdout`
	`./pipex /dev/urandom strings nl tee /dev/stdout`
	- prints and count INDEFINITELY printable character sequences from 
	/dev/random that are at least 4 bytes long
	- `$SHELL` does not give back the prompt (`strings` has always something
	to read)
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

### Mixed dependence commands tests

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | head > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" head /dev/stdout`
	- displays 10 `YESYESYES` on stdout
	- `$SHELL` displays the prompt

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | strings | tee | head > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" strings tee head /dev/stdout`
	- displays 10 `YESYESYES` on stdout
	- `$SHELL` displays the prompt

## What could possibly go wrong?

### ./pipex level

#### Wrong number of arguments (argc != 5)

- [x] Expected error message
	- `pipex: Invalid argument`
	- `usage: pipex <file1> <cmd1> <cmd2> <file2>`
	- Examples:
		- `./pipex`
		- `./pipex infile cmd outfile`
	- [x] Leak protected?

#### Swapped order (argc != 5)

- [x] Expected error message
	- [Error message dependent on the permission associated to 
	the positional arg]
	- Examples:
		- `./pipex strings /dev/random head /dev/stdout`
		- `./pipex /dev/random strings head /dev/random /dev/stdout`
	- [x] Leak protected?

### < file1 level

#### infile (argv[1]) does not exist:
	- [x] Expected error message
		- `bash: <filename>: No such file or directory`
		- `pipex: <filename>: No such file or directory`
		- Examples:
			- `< /dev/gf tee | fold -w 1 > /dev/stdout`
			- `./pipex /dev/gf tee "fold -w 1" /dev/stdout`
			- `< /dev/gf tee | fold -w 1 | nl > /dev/stdout`
			- `./pipex /dev/gf tee cat "fold -w 1" nl /dev/stdout`
		- [x] Leak protected?

#### infile (argv[1]) exists but its folder is not searchable (no x permission)
	- [x] Expected error message
		- `bash: <folder>/<filename>: Permission denied`
		- `pipex: <folder>/<filename>: Permission denied`
		- Example
			- `< ftest/infile tee | cat > /dev/stdout`
			- `./pipex ftest/infile tee cat /dev/stdout`
		- [x] Leak protected?

#### infile (argv[1]) is not readable (no r permission):
	- [x] Expected error message
		- `bash: <filename>: Permission denied`
		- `pipex: <filename>: Permission denied`
		- Examples:
			- `< test/finfile tee | cat > /dev/stdout`
			- `./pipex test/finfile tee cat /dev/stdout`
			- `< test/finfile tee | cat | fold -w 1 | nl > /dev/stdout`
			- `./pipex test/finfile tee cat "fold -w 1" nl /dev/stdout`
		- [x] Leak protected?

#### infile (argv[1]) is a directory:
	- [x] Expected error message
		- `<command>: read error: Is a directory` (depend on the command)
		- (difference in the command path because of execve)
		- Examples:
			- `< . tee | cat > /dev/stdout`
			- `./pipex . tee cat /dev/stdout`
			- `< . tee | yes | head -3 > /dev/stdout`
			- `./pipex . tee yes "head -3" /dev/stdout`
		- [x] Leak protected?

### cmd1 | cmd2 level

#### cdm1 (argv[2]) or cmd2 (argv[3]) is NOT executable:
	- [x] Expected error message
		- `bash: <cmd>: No such file or directory` or `bash: <cmd>: Permission
		denied`
		- `pipex: <cmd>: No such file or directory` or `pipex: <cmd>: Permission
		denied`
		- Examples:
			- `< /dev/random test/fcmd | nl > /dev/stdout`
			- `./pipex /dev/random test/fcmd nl /dev/stdout`
			- `< /dev/random tee | test/fcmd > /dev/stdout`
			- `./pipex /dev/random tee test/fcmd /dev/stdout`
		- [x] Leak protected?

#### cdm1 (argv[2]) or cmd2 (argv[3]) does not exist (not found in $PATH):
	- [x] Expected error message
		- `bash: <cmd>: command not found`
		- `pipex: <cmd>: command not found`
		- Example:
			- `< /dev/random tee | fcmd > /dev/stdout`
			- `./pipex /dev/random tee fcmd /dev/stdout`

			- `< /dev/random fcmd | fcmd > /dev/stdout`
			- `./pipex /dev/random fcmd fcmd /dev/stdout`
			
			- `< /dev/random test/cmd1 | test/cmd2 | fcmd > /dev/stdout`
			- `./pipex /dev/random test/cmd1 test/cmd2 fcmd /dev/stdout`
		- [x] Leak protected?

#### $PATH is missing:
	- [x] Expected error message
		- [No error message expected]
		- Example:
			- `env -u PATH < /dev/random tee | head -c 80 | nl > /dev/stdout`
			- `env -u PATH ./pipex /dev/random tee "head -c 80" nl /dev/stdout`
		- [x] Leak protected?
			- [Test it in a subshell with no PATH]

### > file2 level
	
#### outfile (argv[4]) does not exist:
	- [x] Expected error message
		- [No error message]
		- `outfile` is CREATED and then written upon (IF THE FOLDER is writable)
		- Example:
			- `< /dev/random strings | head > test/outfile`
			- `./pipex /dev/random strings head test/outfile`
		- [x] Leak protected?

#### outfile (argv[4]) does not exist and the parent folder is not searchable:
	- [x] Expected error message
		- `bash: <filename>: Permission denied`
		- `pipex: <filename>: Permission denied`
		- Example:
			- `< /dev/random strings | head > ftest/outfile`
			- `./pipex /dev/random strings head ftest/outfile`
		- [x] Leak protected?

#### outfile (argv[4]) exists but is not writable:
	- [x] Expected error message
		- `bash: <filename>: Permission denied`
		- `pipex: <filename>: Permission denied`
		- Example:
			- `< /dev/random strings | head > test/foutfile`
			- `./pipex /dev/random strings head test/foutfile`
		- [x] Leak protected?

#### outfile (argv[4]) is a directory:
	- [x] Expected error message
		- `bash: <directory>: is a directory`
		- `pipex: <directory>: is a directory`
		- Example:
			- `< /dev/random strings | head > .`
			- `./pipex /dev/random strings head .`
		- [x] Leak protected?
