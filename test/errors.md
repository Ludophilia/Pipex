# Pipex errors analysis

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

## What could possibly go wrong?

### ./pipex level

- The number of arguments passed to the program is different from 4 (argc != 5)

### < file1 level

- argv[1] does not exist:
	- `bash: <filename>: No such file or directory`
- argv[1] is a directory:
	- `<command>: read error: Is a directory`
- argv[1] is not readable:
	- `bash: <filename>: Permission denied`

### cmd1 | cmd2 level

- argv[2] or argv[3] is NOT executable:
	- `bash: <cmd>: Permission denied`
- argv[2] or argv[3] does not exist (not found in $PATH):
	- `<cmd>: command not found`
- ~~argv[2] does not read from stdin, nor write to stdout~~

### > file2 level

- argv[4] does not exist:
	- `bash: <filename>: No such file or directory`
- argv[4] is not writable:
	- `bash: <filename>: Permission denied`
- argv[4] is a directory:
	- `zsh: is a directory: <directory>`
